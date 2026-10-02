#pragma once
#include <QString>

struct ShortcutInfo {
    QString captureShortcut;
    QString historyShortcut;
    bool globalRegistrationSucceeded = false;
    QString registrationMethod; // "portal", "gsettings", "manual"
    QString setupInstructions; // human-readable instructions for desktop binding
};

ShortcutInfo buildGnomeShortcutInstructions(const QString& captureCmd, const QString& historyCmd);
