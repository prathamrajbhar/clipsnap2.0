#pragma once
#include "ClipboardBackend.h"
#include <QDBusAbstractAdaptor>
#include <QDBusConnection>

class GnomeClipboardBackend : public ClipboardBackend {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "app.clipsnap.Monitor1")
public:
    explicit GnomeClipboardBackend(QObject* parent = nullptr);
    ~GnomeClipboardBackend() override;

    void startMonitoring() override;
    void stopMonitoring() override;
    bool isMonitoring() const override;
    QString backendName() const override { return "GNOME Extension (Background)"; }

    // D-Bus property exposed to extension
    Q_PROPERTY(bool MonitoringActive READ isMonitoring)

public slots:
    // D-Bus methods
    Q_NOREPLY void ClipboardChanged(const QString& content_type, const QString& data);
    void Ping();

private:
    bool m_monitoring = false;
    bool m_registered = false;
};
