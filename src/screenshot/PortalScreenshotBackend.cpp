#include "PortalScreenshotBackend.h"
#include <QDBusMessage>
#include <QDBusReply>
#include <QUuid>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

PortalScreenshotBackend::PortalScreenshotBackend(QObject* parent)
    : ScreenshotBackend(parent)
{
}

#include <QUrl>
#include <QScreen>
#include <QPixmap>
#include <QGuiApplication>
#include <QDBusPendingCall>
#include <QDBusPendingCallWatcher>
#include <QThread>
#include <QDir>
#include <QDateTime>

static bool isAllBlack(const QImage& img) {
    if (img.isNull()) return true;
    int w = img.width();
    int h = img.height();
    if (w <= 10 || h <= 10) return true;
    for (int y = h / 5; y < h; y += h / 5) {
        for (int x = w / 5; x < w; x += w / 5) {
            QRgb p = img.pixel(x, y);
            if (qRed(p) > 8 || qGreen(p) > 8 || qBlue(p) > 8) {
                return false;
            }
        }
    }
    return true;
}

void PortalScreenshotBackend::startCapture()
{
    qInfo() << "Starting screenshot capture...";
    // 1. Direct Native GNOME Compositor Capture via Mutter DBus
    // Acquire the allowed sender name org.gnome.Screenshot on the session bus
    m_dbus.registerService("org.gnome.Screenshot");

    QString tempShotPath = QDir::tempPath() + "/clipsnap_cap_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".png";
    QFile::remove(tempShotPath);

    QDBusMessage gnomeMsg = QDBusMessage::createMethodCall(
        "org.gnome.Shell.Screenshot",
        "/org/gnome/Shell/Screenshot",
        "org.gnome.Shell.Screenshot",
        "Screenshot"
    );
    gnomeMsg << false << false << tempShotPath; // include_cursor=false, flash=false, filename=tempShotPath
    QDBusMessage reply = m_dbus.call(gnomeMsg);
    if (reply.type() == QDBusMessage::ReplyMessage) {
        bool ok = !reply.arguments().isEmpty() && reply.arguments().at(0).toBool();
        QString pathUsed = reply.arguments().size() > 1 ? reply.arguments().at(1).toString() : tempShotPath;
        if (pathUsed.isEmpty()) pathUsed = tempShotPath;

        for (int i = 0; i < 20; ++i) {
            if (QFile::exists(pathUsed)) {
                QImage image(pathUsed);
                if (!image.isNull() && !isAllBlack(image)) {
                    QFile::remove(pathUsed);
                    qInfo() << "Emitting captureComplete with image size:" << image.size();
                    emit captureComplete(image, QRect());
                    return;
                }
            }
            QThread::msleep(25);
        }
        QFile::remove(pathUsed);
    } else {
        qWarning() << "GNOME Screenshot direct call failed:" << reply.errorMessage();
    }

    // 2. Try GNOME Extension Service (Direct compositor screenshot if active)
    QString extTempPath = QDir::tempPath() + "/clipsnap_ext_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".png";
    QFile::remove(extTempPath);
    QDBusMessage extMsg = QDBusMessage::createMethodCall(
        "app.clipsnap.ExtensionService",
        "/app/clipsnap/ExtensionService",
        "app.clipsnap.ExtensionService",
        "TakeScreenshot"
    );
    extMsg << extTempPath;
    QDBusReply<bool> extReply = m_dbus.call(extMsg);
    if (extReply.isValid() && extReply.value()) {
        for (int i = 0; i < 15; ++i) {
            if (QFile::exists(extTempPath)) {
                QImage image(extTempPath);
                if (!image.isNull() && !isAllBlack(image)) {
                    QFile::remove(extTempPath);
                    emit captureComplete(image, QRect());
                    return;
                }
            }
            QThread::msleep(25);
        }
        QFile::remove(extTempPath);
    }

    // 3. Instant native screen grab (for X11 or compositors allowing X11 grab)
    QScreen* screen = QGuiApplication::primaryScreen();
    if (screen) {
        QPixmap pix = screen->grabWindow(0);
        QImage img = pix.toImage();
        if (!img.isNull() && img.width() > 200 && img.height() > 200 && !isAllBlack(img)) {
            emit captureComplete(img, QRect());
            return;
        }
    }

    // 4. Fallback to XDG Desktop Portal for other Wayland compositors
    QString token = "clipsnap_" + QUuid::createUuid().toString(QUuid::WithoutBraces);
    QVariantMap options;
    options.insert("interactive", false);
    options.insert("modal", true);
    options.insert("handle_token", token);

    // Connect to Response signal before calling method
    m_dbus.connect(
        QString(),
        QString(),
        "org.freedesktop.portal.Request",
        "Response",
        this,
        SLOT(onPortalResponse(uint,QVariantMap))
    );

    QDBusMessage msg = QDBusMessage::createMethodCall(
        "org.freedesktop.portal.Desktop",
        "/org/freedesktop/portal/desktop",
        "org.freedesktop.portal.Screenshot",
        "Screenshot"
    );
    msg << QString() << options;

    QDBusPendingCall pendingCall = m_dbus.asyncCall(msg);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *call) {
        QDBusPendingReply<QDBusObjectPath> reply = *call;
        call->deleteLater();
        if (reply.isError()) {
            qWarning() << "Screenshot portal call error:" << reply.error().message();
            emit captureError("Failed to call screenshot portal: " + reply.error().message());
        }
    });
}

void PortalScreenshotBackend::connectToResponse(const QDBusObjectPath& requestPath)
{
    Q_UNUSED(requestPath);
}

void PortalScreenshotBackend::onPortalResponse(uint response, QVariantMap results)
{
    if (response == 0) {
        QString uri = results.value("uri").toString();
        QString localPath;
        if (uri.startsWith("file://")) {
            localPath = QUrl(uri).toLocalFile();
        } else {
            localPath = uri;
        }
        
        QImage image(localPath);
        if (image.isNull()) {
            emit captureError("Failed to load captured image from " + localPath);
        } else {
            emit captureComplete(image, QRect());
        }
        QFile::remove(localPath);
    } else if (response == 1) {
        emit captureCancelled();
    } else {
        emit captureError("Screenshot portal failed with response code: " + QString::number(response));
    }
}
