#pragma once

#include "ScreenshotBackend.h"
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QVariantMap>

class PortalScreenshotBackend : public ScreenshotBackend {
    Q_OBJECT
public:
    explicit PortalScreenshotBackend(QObject* parent = nullptr);
    Q_INVOKABLE void startCapture() override;
    Q_INVOKABLE QString backendName() const override { return "XDG Screenshot Portal"; }
    Q_INVOKABLE bool supportsNativeRegion() const override { return false; } // portal v2 on GNOME = full screen

private slots:
    void onPortalResponse(uint response, QVariantMap results);

private:
    void connectToResponse(const QDBusObjectPath& requestPath);
    QDBusConnection m_dbus{QDBusConnection::sessionBus()};
    QString m_responseMatchRule;
};
