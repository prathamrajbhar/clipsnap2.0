const { Gio, GLib, Shell } = imports.gi;
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
            
            // Check if service is running
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
                        // Name exists, app is active
                        if (dbusProxy) {
                            dbusProxy.ClipboardChangedSync('text', text);
                        }
                    } catch (e) {
                        // App is not running, skip
                    }
                }
            );
        }
    });
}
