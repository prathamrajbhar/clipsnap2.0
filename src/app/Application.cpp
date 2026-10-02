#include "Application.h"
#include "../ipc/SingleInstance.h"
#include "../settings/Settings.h"
#include "../history/HistoryRepository.h"
#include "../history/HistoryItem.h"
#include "../clipboard/QtClipboardBackend.h"
#include "../clipboard/GnomeClipboardBackend.h"
#include "../capability/CapabilityDetector.h"
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <QCryptographicHash>
#include <QBuffer>
#include <iostream>

Application::Application(QObject* parent) : QObject(parent) {
    m_history = new HistoryRepository(this);
}

Application::~Application() {
}

void Application::initialize() {
    Settings* s = Settings::instance();
    QString dbPath = s->dataDir() + "/history.db";
    m_history->open(dbPath);

    auto wireBackend = [this](ClipboardBackend* backend) {
        connect(backend, &ClipboardBackend::clipboardTextChanged, this, [this](const QString& text) {
            if (!Settings::instance()->monitoringEnabled()) return;
            HistoryItem item;
            item.createdAt = QDateTime::currentDateTime();
            item.lastAccessedAt = item.createdAt;
            item.origin = "clipboard";
            item.searchableText = text;
            
            QByteArray textData = text.toUtf8();
            item.contentHash = QCryptographicHash::hash(textData, QCryptographicHash::Sha256);
            item.storageSizeBytes = textData.size();
            
            MimeRepresentation rep;
            rep.mimeType = "text/plain";
            rep.inlineData = textData;
            item.representations.append(rep);
            
            m_history->addItem(item);
        });

        connect(backend, &ClipboardBackend::clipboardImageChanged, this, [this](const QImage& image) {
            if (!Settings::instance()->monitoringEnabled()) return;
            saveImageToHistory(image, "clipboard");
        });

        if (Settings::instance()->monitoringEnabled()) {
            backend->startMonitoring();
        }
    };

    // Always start QtClipboardBackend for universal, dependable capture
    m_clipboardBackend = new QtClipboardBackend(this);
    wireBackend(m_clipboardBackend);

    // If GNOME extension is active on D-Bus, wire it as well
    Capabilities caps = CapabilityDetector::detect();
    if (caps.hasGnomeExtension) {
        GnomeClipboardBackend* gnomeBackend = new GnomeClipboardBackend(this);
        wireBackend(gnomeBackend);
    }
}

void Application::handleCommand(const QStringList& args) {
    qInfo() << "Application::handleCommand:" << args;
    if (args.isEmpty()) {
        emit historyRequested();
        return;
    }

    QString cmd = args.first().trimmed().toLower();
    if (cmd == "capture" || cmd == "--capture" || cmd == "--screenshot" || cmd == "-s") {
        emit captureRequested();
    } else if (cmd == "history" || cmd == "--history" || cmd == "-h" || cmd == "show") {
        emit historyRequested();
    } else if (cmd == "pause" || cmd == "--pause") {
        Settings::instance()->setMonitoringEnabled(false);
        m_clipboardBackend->stopMonitoring();
        emit pauseRequested();
    } else if (cmd == "resume" || cmd == "--resume") {
        Settings::instance()->setMonitoringEnabled(true);
        m_clipboardBackend->startMonitoring();
        emit resumeRequested();
    } else if (cmd == "doctor") {
        std::cout << "Running diagnostics..." << std::endl;
    } else if (cmd == "--version" || cmd == "-v") {
        std::cout << "clipsnap " << QCoreApplication::applicationVersion().toStdString() << std::endl;
    } else {
        emit historyRequested();
    }
}

void Application::saveImageToHistory(const QImage& image, const QString& origin) {
    if (image.isNull()) return;

    HistoryItem item;
    item.createdAt = QDateTime::currentDateTime();
    item.lastAccessedAt = item.createdAt;
    item.origin = origin;

    QByteArray imgData;
    QBuffer buffer(&imgData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    item.contentHash = QCryptographicHash::hash(imgData, QCryptographicHash::Sha256);
    item.storageSizeBytes = imgData.size();

    QString filename = QString::number(item.createdAt.toMSecsSinceEpoch()) + ".png";
    QString payloadsDir = Settings::instance()->dataDir() + "/payloads";
    QDir().mkpath(payloadsDir);
    QString payloadPath = payloadsDir + "/" + filename;

    QFile file(payloadPath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(imgData);
        file.close();
    }

    QString thumbsDir = Settings::instance()->dataDir() + "/thumbnails";
    QDir().mkpath(thumbsDir);
    QString thumbPath = thumbsDir + "/" + filename;
    QImage thumb = image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    thumb.save(thumbPath, "PNG");
    item.thumbnailPath = thumbPath;

    MimeRepresentation rep;
    rep.mimeType = "image/png";
    rep.payloadPath = payloadPath;
    item.representations.append(rep);

    m_history->addItem(item);
}

void Application::checkClipboardNow() {
    if (m_clipboardBackend) {
        m_clipboardBackend->checkClipboard();
    }
}

