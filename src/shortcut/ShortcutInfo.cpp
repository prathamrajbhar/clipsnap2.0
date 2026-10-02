#include "ShortcutInfo.h"

ShortcutInfo buildGnomeShortcutInstructions(const QString& captureCmd, const QString& historyCmd) {
    ShortcutInfo info;
    info.captureShortcut = "Alt+Shift+S";
    info.historyShortcut = "Alt+H";
    info.globalRegistrationSucceeded = false;
    info.registrationMethod = "manual";
    info.setupInstructions = QString(
        "To set up shortcuts in GNOME:\n"
        "1. Open GNOME Settings -> Keyboard -> View and Customize Shortcuts -> Custom Shortcuts\n"
        "2. Add a new shortcut for Capture:\n"
        "   Name: ClipSnap Capture\n"
        "   Command: %1\n"
        "   Shortcut: %2\n"
        "3. Add a new shortcut for History:\n"
        "   Name: ClipSnap History\n"
        "   Command: %3\n"
        "   Shortcut: %4\n"
    ).arg(captureCmd, info.captureShortcut, historyCmd, info.historyShortcut);
    
    return info;
}
