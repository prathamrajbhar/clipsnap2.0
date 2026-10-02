#pragma once

#include <QString>

struct Capabilities {
    bool hasX11 = false;
    bool hasWayland = false;
    bool isGnome = false;
    bool hasScreenshotPortal = false;
    int screenshotPortalVersion = 0;
    bool hasGlobalShortcutsPortal = false;
    bool hasNotificationPortal = false;
    bool hasGnomeExtension = false;
    QString sessionType;
    QString desktopEnv;
};

class CapabilityDetector {
public:
    static Capabilities detect();
    static bool installGnomeExtension();
    static bool configureGnomeShortcuts(const QString& binaryPath = QString());
    static bool setupDesktopIntegration(const QString& binaryPath = QString());
    static bool removeDesktopIntegration();
};
