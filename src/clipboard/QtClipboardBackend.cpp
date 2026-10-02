#include "QtClipboardBackend.h"
#include <QGuiApplication>
#include <QMimeData>
#include <QCryptographicHash>
#include <QBuffer>
#include <QDebug>

QtClipboardBackend::QtClipboardBackend(QObject* parent)
    : ClipboardBackend(parent)
{
    m_clipboard = QGuiApplication::clipboard();
    m_pollTimer = new QTimer(this);
    m_pollTimer->setInterval(350);
    connect(m_pollTimer, &QTimer::timeout, this, &QtClipboardBackend::checkClipboard);
}

QtClipboardBackend::~QtClipboardBackend() {
    stopMonitoring();
}

void QtClipboardBackend::startMonitoring() {
    if (m_monitoring) return;
    m_monitoring = true;
    connect(m_clipboard, &QClipboard::dataChanged, this, &QtClipboardBackend::onClipboardDataChanged);
    m_pollTimer->start();
    
    // Seed initial hash to avoid re-capturing previous session on clean startup
    const QMimeData* mime = m_clipboard ? m_clipboard->mimeData() : nullptr;
    if (mime && mime->hasText()) {
        m_lastHash = QCryptographicHash::hash(mime->text().toUtf8(), QCryptographicHash::Sha256);
    }
}

void QtClipboardBackend::stopMonitoring() {
    if (!m_monitoring) return;
    m_monitoring = false;
    if (m_clipboard) {
        disconnect(m_clipboard, &QClipboard::dataChanged, this, &QtClipboardBackend::onClipboardDataChanged);
    }
    m_pollTimer->stop();
}

bool QtClipboardBackend::isMonitoring() const {
    return m_monitoring;
}

void QtClipboardBackend::onClipboardDataChanged() {
    checkClipboard();
}

void QtClipboardBackend::checkClipboard() {
    if (!m_monitoring || !m_clipboard) return;

    const QMimeData* mimeData = m_clipboard->mimeData();
    if (!mimeData) return;
    
    // Concealed content hint from password managers
    if (mimeData->hasFormat("x-kde-passwordManagerHint") || 
        mimeData->hasFormat("application/x-nspasteboard-concealed-type")) {
        return;
    }

    if (mimeData->hasImage()) {
        QImage img = qvariant_cast<QImage>(mimeData->imageData());
        if (!img.isNull()) {
            QByteArray imgBytes;
            QBuffer buffer(&imgBytes);
            buffer.open(QIODevice::WriteOnly);
            img.save(&buffer, "PNG");
            QByteArray hash = QCryptographicHash::hash(imgBytes, QCryptographicHash::Sha256);
            if (hash != m_lastHash) {
                m_lastHash = hash;
                emit clipboardImageChanged(img);
            }
            return;
        }
    }

    if (mimeData->hasText()) {
        QString text = mimeData->text();
        if (!text.isEmpty()) {
            QByteArray hash = QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha256);
            if (hash != m_lastHash) {
                m_lastHash = hash;
                emit clipboardTextChanged(text);
            }
        }
    }
}

