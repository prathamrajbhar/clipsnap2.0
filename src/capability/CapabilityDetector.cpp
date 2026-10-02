#include "CapabilityDetector.h"
#include <QProcessEnvironment>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QCoreApplication>
#include <QSet>

Capabilities CapabilityDetector::detect() {
    Capabilities caps;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    caps.desktopEnv = env.value("XDG_CURRENT_DESKTOP", "").toLower();
    caps.sessionType = env.value("XDG_SESSION_TYPE", "").toLower();

    if (caps.sessionType == "wayland") {
        caps.hasWayland = true;
    } else if (caps.sessionType == "x11") {
        caps.hasX11 = true;
    }

    if (caps.desktopEnv.contains("gnome")) {
        caps.isGnome = true;
    }

    if (env.contains("WAYLAND_DISPLAY")) {
        caps.hasWayland = true;
    }
    if (env.contains("DISPLAY")) {
        caps.hasX11 = true;
    }

    QDBusConnection bus = QDBusConnection::sessionBus();
    
    QDBusInterface portalIntf("org.freedesktop.portal.Desktop",
                              "/org/freedesktop/portal/desktop",
                              "org.freedesktop.DBus.Properties",
                              bus);
    if (portalIntf.isValid()) {
        QDBusMessage call = QDBusMessage::createMethodCall("org.freedesktop.portal.Desktop",
                                                           "/org/freedesktop/portal/desktop",
                                                           "org.freedesktop.DBus.Properties",
                                                           "Get");
        call << "org.freedesktop.portal.Screenshot" << "version";
        QDBusReply<QVariant> reply = bus.call(call);
        if (reply.isValid()) {
            caps.hasScreenshotPortal = true;
            caps.screenshotPortalVersion = reply.value().toInt();
        }
    }

    QDBusInterface shortcutsIntf("org.freedesktop.portal.Desktop",
                                 "/org/freedesktop/portal/desktop",
                                 "org.freedesktop.portal.GlobalShortcuts",
                                 bus);
    if (shortcutsIntf.isValid()) {
        caps.hasGlobalShortcutsPortal = true;
    }

    QDBusInterface notifIntf("org.freedesktop.portal.Desktop",
                             "/org/freedesktop/portal/desktop",
                             "org.freedesktop.portal.Notification",
                             bus);
    if (notifIntf.isValid()) {
        caps.hasNotificationPortal = true;
    }

    // Check if ClipSnap GNOME extension is actually active on D-Bus
    if (bus.interface() && bus.interface()->isServiceRegistered("app.clipsnap.ExtensionService")) {
        caps.hasGnomeExtension = true;
    }

    return caps;
}

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QCoreApplication>

bool CapabilityDetector::installGnomeExtension() {
    QString targetDir = QDir::homePath() + "/.local/share/gnome-shell/extensions/clipsnap@clipsnap.app";
    QDir().mkpath(targetDir);

    // metadata.json
    QString metadataJson = R"({
  "name": "ClipSnap Clipboard Monitor",
  "description": "Forwards clipboard change events to ClipSnap via D-Bus. Requires user consent.",
  "uuid": "clipsnap@clipsnap.app",
  "shell-version": ["42", "43", "44", "45", "46", "47"],
  "version": 1,
  "url": ""
})";

    // extension.js
    QString extensionJs = R"(const { Gio, GLib, Shell } = imports.gi;
imports.gi.versions.St = '13';
const St = imports.gi.St;

const DBUS_INTERFACE = `
<node>
  <interface name="app.clipsnap.Monitor1">
    <method name="ClipboardChanged">
      <arg name="content_type" type="s" direction="in"/>
      <arg name="data" type="s" direction="in"/>
    </method>
  </interface>
</node>
`;

const DBUS_SERVICE_INTERFACE = `
<node>
  <interface name="app.clipsnap.ExtensionService">
    <method name="TakeScreenshot">
      <arg name="path" type="s" direction="in"/>
      <arg name="success" type="b" direction="out"/>
    </method>
  </interface>
</node>
`;

let clipboard = null;
let timeoutId = null;
let lastText = null;
let dbusProxy = null;
let dbusImpl = null;
let dbusNameId = null;

function init() {
}

function enable() {
    clipboard = St.Clipboard.get_default();
    
    const ProxyWrapper = Gio.DBusProxy.makeProxyWrapper(DBUS_INTERFACE);
    dbusProxy = new ProxyWrapper(
        Gio.DBus.session,
        'app.clipsnap.Monitor',
        '/app/clipsnap/Monitor'
    );
    
    timeoutId = GLib.timeout_add(GLib.PRIORITY_DEFAULT, 500, () => {
        checkClipboard();
        return GLib.SOURCE_CONTINUE;
    });

    try {
        dbusImpl = Gio.DBusExportedObject.wrapJSObject(DBUS_SERVICE_INTERFACE, {
            TakeScreenshot(path) {
                try {
                    let screenshot = new Shell.Screenshot();
                    screenshot.screenshot(false, false, path, (s, success, area, file) => {
                        // finished
                    });
                    return true;
                } catch (err) {
                    return false;
                }
            }
        });
        dbusImpl.export(Gio.DBus.session, '/app/clipsnap/ExtensionService');
        dbusNameId = Gio.DBus.session.own_name('app.clipsnap.ExtensionService', Gio.BusNameOwnerFlags.NONE, null, null);
    } catch (e) {
    }
}

function disable() {
    if (timeoutId) {
        GLib.source_remove(timeoutId);
        timeoutId = null;
    }
    if (dbusImpl) {
        dbusImpl.unexport();
        dbusImpl = null;
    }
    if (dbusNameId) {
        Gio.DBus.session.unown_name(dbusNameId);
        dbusNameId = null;
    }
    dbusProxy = null;
    clipboard = null;
    lastText = null;
}

function checkClipboard() {
    clipboard.get_text(St.ClipboardType.CLIPBOARD, (cb, text) => {
        if (text && text !== lastText) {
            lastText = text;
            
            Gio.DBus.session.call(
                'org.freedesktop.DBus',
                '/org/freedesktop/DBus',
                'org.freedesktop.DBus',
                'GetNameOwner',
                new GLib.Variant('(s)', ['app.clipsnap.Monitor']),
                null,
                Gio.DBusCallFlags.NONE,
                -1,
                null,
                (connection, res) => {
                    try {
                        connection.call_finish(res);
                        if (dbusProxy) {
                            dbusProxy.ClipboardChangedSync('text', text);
                        }
                    } catch (e) {
                    }
                }
            );
        }
    });
}
)";

    // dbus-interface.xml
    QString dbusXml = R"(<!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN"
 "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">
<node>
  <interface name="app.clipsnap.Monitor1">
    <method name="ClipboardChanged">
      <arg name="content_type" type="s" direction="in"/>
      <arg name="data" type="s" direction="in"/>
    </method>
    <method name="Ping"/>
    <property name="MonitoringActive" type="b" access="read"/>
  </interface>
</node>
)";

    auto writeFile = [](const QString& path, const QString& content) -> bool {
        QFile f(path);
        if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            f.write(content.toUtf8());
            f.close();
            return true;
        }
        return false;
    };

    bool ok1 = writeFile(targetDir + "/metadata.json", metadataJson);
    bool ok2 = writeFile(targetDir + "/extension.js", extensionJs);
    bool ok3 = writeFile(targetDir + "/dbus-interface.xml", dbusXml);

    if (ok1 && ok2 && ok3) {
        // Try enabling via gnome-extensions CLI
        QProcess::execute("gnome-extensions", QStringList() << "enable" << "clipsnap@clipsnap.app");
        return true;
    }
    return false;
}

bool CapabilityDetector::configureGnomeShortcuts(const QString& customBinaryPath) {
    QString binPath = customBinaryPath;
    if (binPath.isEmpty()) {
        binPath = QDir::homePath() + "/.local/bin/clipsnap";
    }

    // 1. Reset GNOME Shell native screenshot UI keybinding so it doesn't intercept ClipSnap's shortcut
    QProcess::execute("gsettings", QStringList() << "set" 
                      << "org.gnome.shell.keybindings" 
                      << "show-screenshot-ui" 
                      << "['Print']");

    // 2. Set history shortcut (Alt+H) via custom media-keys
    QString custom0 = "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/";
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom0)
                      << "name" << "ClipSnap History");
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom0)
                      << "command" << QString("%1 history").arg(binPath));
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom0)
                      << "binding" << "<Alt>h");

    // 3. Set capture shortcut (Alt+Shift+S / Shift+Alt+S) via custom media-keys
    QString custom1 = "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/";
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom1)
                      << "name" << "ClipSnap Capture");
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom1)
                      << "command" << QString("%1 capture").arg(binPath));
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom1)
                      << "binding" << "<Shift><Alt>s");

    QString custom2 = "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom2/";
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom2)
                      << "name" << "ClipSnap Capture Alt");
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom2)
                      << "command" << QString("%1 capture").arg(binPath));
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom2)
                      << "binding" << "<Alt><Shift>s");

    // Also support Super+Shift+S (standard snipping tool shortcut)
    QString custom3 = "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom3/";
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom3)
                      << "name" << "ClipSnap Capture Super");
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom3)
                      << "command" << QString("%1 capture").arg(binPath));
    QProcess::execute("gsettings", QStringList() << "set" 
                      << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(custom3)
                      << "binding" << "<Super><Shift>s");

    // 4. Set custom-keybindings array
    QString arrayVal = QString("['%1', '%2', '%3', '%4']").arg(custom0, custom1, custom2, custom3);
    QProcess::execute("gsettings", QStringList() << "set" 
                      << "org.gnome.settings-daemon.plugins.media-keys" 
                      << "custom-keybindings" << arrayVal);

    return true;
}

bool CapabilityDetector::setupDesktopIntegration(const QString& customBinaryPath) {
    QString currentExe = customBinaryPath.isEmpty() ? QCoreApplication::applicationFilePath() : customBinaryPath;
    
    QString targetBin;
    if (currentExe == "/usr/bin/clipsnap" || (!customBinaryPath.isEmpty() && customBinaryPath.startsWith("/usr/"))) {
        targetBin = "/usr/bin/clipsnap";
    } else {
        // Copy/symlink current binary to ~/.local/bin/clipsnap for user/local installs
        QString localBinDir = QDir::homePath() + "/.local/bin";
        QDir().mkpath(localBinDir);
        targetBin = localBinDir + "/clipsnap";
        
        if (currentExe != targetBin && QFile::exists(currentExe)) {
            QFile::remove(targetBin);
            QFile::copy(currentExe, targetBin);
            QFile::setPermissions(targetBin, QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner |
                                             QFileDevice::ReadGroup | QFileDevice::ExeGroup |
                                             QFileDevice::ReadOther | QFileDevice::ExeOther);
        }
    }

    installGnomeExtension();
    configureGnomeShortcuts(targetBin);

    // Update systemd user service
    QString systemdDir = QDir::homePath() + "/.config/systemd/user";
    QDir().mkpath(systemdDir);
    QString servicePath = systemdDir + "/clipsnap.service";
    QFile serviceFile(servicePath);
    if (serviceFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QString s = QString(
            "[Unit]\n"
            "Description=ClipSnap Area Screenshot & Clipboard Manager\n"
            "PartOf=graphical-session.target\n"
            "After=graphical-session.target\n\n"
            "[Service]\n"
            "ExecStart=%1\n"
            "Restart=always\n"
            "RestartSec=2\n\n"
            "[Install]\n"
            "WantedBy=graphical-session.target\n"
        ).arg(targetBin);
        serviceFile.write(s.toUtf8());
        serviceFile.close();
        QProcess::execute("systemctl", QStringList() << "--user" << "daemon-reload");
        QProcess::execute("systemctl", QStringList() << "--user" << "enable" << "clipsnap.service");
    }

    return true;
}

bool CapabilityDetector::removeDesktopIntegration() {
    // 1. Stop and disable systemd user service
    QProcess::execute("systemctl", QStringList() << "--user" << "stop" << "clipsnap.service");
    QProcess::execute("systemctl", QStringList() << "--user" << "disable" << "clipsnap.service");

    QString systemdDir = QDir::homePath() + "/.config/systemd/user";
    QFile::remove(systemdDir + "/clipsnap.service");
    QProcess::execute("systemctl", QStringList() << "--user" << "daemon-reload");

    // 2. Remove GNOME custom shortcut keybindings
    for (int i = 0; i < 4; ++i) {
        QString path = QString("/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom%1/").arg(i);
        QProcess::execute("gsettings", QStringList() << "reset-recursively"
                          << QString("org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:%1").arg(path));
    }
    QProcess::execute("gsettings", QStringList() << "reset"
                      << "org.gnome.settings-daemon.plugins.media-keys" << "custom-keybindings");

    // 3. Disable and remove user GNOME extension
    QProcess::execute("gnome-extensions", QStringList() << "disable" << "clipsnap@clipsnap.app");
    QString extDir = QDir::homePath() + "/.local/share/gnome-shell/extensions/clipsnap@clipsnap.app";
    QDir(extDir).removeRecursively();

    // 4. Remove local binary if in ~/.local/bin/clipsnap
    QString localBin = QDir::homePath() + "/.local/bin/clipsnap";
    QFile::remove(localBin);

    return true;
}
