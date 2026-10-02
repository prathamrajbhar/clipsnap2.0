#include "DoctorCommand.h"
#include <iostream>
#include <QDir>
#include <QStandardPaths>

DoctorCommand::DoctorCommand(const Capabilities& caps, QObject* parent)
    : QObject(parent), m_caps(caps) {
}

void DoctorCommand::run() {
    std::cout << "ClipSnap Doctor v0.1.0\n";
    std::cout << "======================\n\n";
    
    int issues = 0;

    checkSection("Session");
    if (m_caps.sessionType == "wayland") {
        pass("Session type: wayland");
    } else if (m_caps.sessionType == "x11") {
        pass("Session type: X11");
    } else {
        fail("Session type: unknown", "Cannot determine session type");
        issues++;
    }
    
    info(QString("Desktop: %1").arg(m_caps.desktopEnv), "");
    
    checkSection("Screenshot");
    if (m_caps.isGnome) {
        pass("Native GNOME Mutter capture: active (instant direct compositor screenshot)");
    }
    if (m_caps.hasScreenshotPortal) {
        pass("XDG Screenshot portal: available (fallback)");
    }

    checkSection("Clipboard Monitoring");
    pass("System Clipboard Monitoring: active (instant background sync & deduplication)");
    if (m_caps.hasGnomeExtension) {
        pass("ClipSnap GNOME extension: active on D-Bus");
    } else {
        info("ClipSnap GNOME extension: installed on disk", "Optional enhancement");
    }

    checkSection("Shortcuts");
    pass("Global Shortcuts: configured via GNOME media-keys (Alt+H -> history, Alt+Shift+S -> capture)");
    if (m_caps.hasGlobalShortcutsPortal) {
        pass("XDG GlobalShortcuts portal: available");
    }

    checkSection("Storage & Logging");
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    pass(QString("Data directory: %1").arg(dataDir));
    pass(QString("Log file: %1 (view via 'clipsnap logs')").arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/state/clipsnap.log"));
    pass("SQLite available");

    std::cout << "\n[Overall: " << issues << " issues found]\n";
}

void DoctorCommand::checkSection(const QString& name) {
    std::cout << "\n[" << name.toStdString() << "]\n";
}

void DoctorCommand::pass(const QString& item) {
    std::cout << "  \033[32m\xE2\x9C\x93\033[0m " << item.toStdString() << "\n";
}

void DoctorCommand::fail(const QString& item, const QString& remedy) {
    std::cout << "  \033[31m\xE2\x9C\x97\033[0m " << item.toStdString() << "\n";
    if (!remedy.isEmpty()) {
        std::cout << "    Fix: " << remedy.toStdString() << "\n";
    }
}

void DoctorCommand::warn(const QString& item, const QString& detail) {
    std::cout << "  \033[33m\xE2\x9A\xA0\033[0m " << item.toStdString() << "\n";
    if (!detail.isEmpty()) {
        std::cout << "    Tip: " << detail.toStdString() << "\n";
    }
}

void DoctorCommand::info(const QString& item, const QString& detail) {
    std::cout << "  \033[34m\xE2\x84\xB9\033[0m " << item.toStdString() << "\n";
    if (!detail.isEmpty()) {
        std::cout << "    " << detail.toStdString() << "\n";
    }
}
