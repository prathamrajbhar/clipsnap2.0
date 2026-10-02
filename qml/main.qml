import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

QtObject {
    id: appRoot

    property var mainWindow: ApplicationWindow {
        id: root
        visible: false
        width: 860
        height: 580
        minimumWidth: 640
        minimumHeight: 420
        title: "ClipSnap - Clipboard & Screenshot Manager"
        flags: Qt.Window

        // Official Ubuntu Yaru Dark Theme Palette
        property color bgColor: "#242424"          // Ubuntu Base Dark
        property color surfaceColor: "#2D2D2D"     // Yaru Card Surface
        property color headerColor: "#1E1E1E"      // Yaru Top Panel
        property color accentColor: "#E95420"      // Canonical Ubuntu Orange
        property color accentHover: "#FF6E38"      // Ubuntu Orange Hover
        property color aubergine: "#5E2750"        // Ubuntu Aubergine
        property color aubergineLight: "#77216F"   // Ubuntu Light Aubergine
        property color borderColor: "#3D3D3D"      // Yaru Stroke / Border
        property color hoverColor: "#383838"        // List Item Hover
        property color textColor: "#FFFFFF"        // High-contrast Primary Text
        property color subTextColor: "#AEA79F"     // Ubuntu Warm Grey
        property color successColor: "#38B44A"     // Ubuntu Green
        property color errorColor: "#DF382C"       // Ubuntu Red

        color: bgColor

        onVisibleChanged: {
            if (visible) {
                app.checkActiveClipboard()
            }
        }

        // Main content: History UI
        HistoryView {
            anchors.fill: parent
        }
    }

    property var cropWindow: CropWindow {
        id: cropOverlay
    }

    property var settingsWindow: SettingsWindow {
        id: settingsDialog
    }

    property var hideTimer: Timer {
        id: timer
        interval: 120
        repeat: false
        onTriggered: screenshotBackend.startCapture()
    }

    property var appConnections: Connections {
        target: app
        function onHistoryRequested() {
            if (root.visible) {
                root.visible = false
                root.hide()
            } else {
                if (cropOverlay.visible) {
                    cropOverlay.visible = false
                    cropOverlay.hide()
                }
                root.visible = true
                root.show()
                root.raise()
                root.requestActivate()
                app.checkActiveClipboard()
            }
        }
        function onCaptureRequested() {
            if (root.visible) {
                root.visible = false
                root.hide()
                timer.restart()
            } else {
                screenshotBackend.startCapture()
            }
        }
        function onSettingsRequested() {
            settingsDialog.show()
            settingsDialog.raise()
            settingsDialog.requestActivate()
        }
    }

    property var screenshotConnections: Connections {
        target: screenshotBackend
        function onCaptureComplete(image, region) {
            console.log("QML onCaptureComplete: captured image size:", image.width, "x", image.height)
            if (root.visible) {
                root.visible = false
                root.hide()
            }
            cropOverlay.showWithImage(image)
        }
        function onCaptureCancelled() {
            console.log("Screenshot cancelled")
        }
        function onCaptureError(message) {
            console.warn("Screenshot error:", message)
        }
        function onCapturePermissionDenied() {
            console.warn("Screenshot: permission denied")
        }
        function onCaptureUnsupported(reason) {
            console.warn("Screenshot unsupported:", reason)
        }
    }
}
