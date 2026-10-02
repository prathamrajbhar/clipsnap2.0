#pragma once
#include "ClipboardBackend.h"
#include <QClipboard>
#include <QTimer>
#include <QByteArray>

class QtClipboardBackend : public ClipboardBackend {
    Q_OBJECT
public:
    explicit QtClipboardBackend(QObject* parent = nullptr);
    ~QtClipboardBackend() override;

    void startMonitoring() override;
    void stopMonitoring() override;
    bool isMonitoring() const override;
    QString backendName() const override { return "Qt System Clipboard"; }
    void checkClipboard() override;

private slots:
    void onClipboardDataChanged();

private:
    bool m_monitoring = false;
    QClipboard* m_clipboard = nullptr;
    QTimer* m_pollTimer = nullptr;
    QByteArray m_lastHash;
};

