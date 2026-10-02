#include "GnomeClipboardBackend.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>

GnomeClipboardBackend::GnomeClipboardBackend(QObject* parent)
    : ClipboardBackend(parent)
{
}

GnomeClipboardBackend::~GnomeClipboardBackend() {
    stopMonitoring();
}

void GnomeClipboardBackend::startMonitoring() {
    if (m_monitoring) return;
    
    if (!m_registered) {
        QDBusConnection bus = QDBusConnection::sessionBus();
        if (bus.registerService("app.clipsnap.Monitor")) {
            bus.registerObject("/app/clipsnap/Monitor", this, QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllProperties);
            m_registered = true;
        } else {
            // Failed to register service, maybe already registered?
            qWarning() << "Failed to register D-Bus service for Gnome extension";
        }
    }
    m_monitoring = true;
}

void GnomeClipboardBackend::stopMonitoring() {
    m_monitoring = false;
    // We can keep the object registered and just return early in the slot, 
    // or we could unregister. Returning early is safer.
}

bool GnomeClipboardBackend::isMonitoring() const {
    return m_monitoring;
}

void GnomeClipboardBackend::ClipboardChanged(const QString& content_type, const QString& data) {
    if (!m_monitoring) return;
    
    if (content_type == "text") {
        emit clipboardTextChanged(data);
    } else if (content_type == "image-available") {
        // The extension tells us an image is available. 
        // We can fetch it via QClipboard since it's now in the Wayland clipboard.
        QClipboard* clipboard = QGuiApplication::clipboard();
        const QMimeData* mime = clipboard->mimeData();
        if (mime && mime->hasImage()) {
            QImage img = qvariant_cast<QImage>(mime->imageData());
            if (!img.isNull()) {
                emit clipboardImageChanged(img);
            }
        }
    }
}

void GnomeClipboardBackend::Ping() {
    // Just an empty slot for the extension to verify connection
}
