import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    id: settingsWindow
    width: 460
    height: 540
    minimumWidth: 400
    minimumHeight: 480
    title: "ClipSnap - Settings"
    color: "#242424"

    ScrollView {
        anchors.fill: parent
        anchors.margins: 20
        contentWidth: availableWidth
        clip: true

        ColumnLayout {
            width: parent.width
            spacing: 16

            // Title
            RowLayout {
                spacing: 10
                Label {
                    text: "⚙"
                    font.pixelSize: 22
                }
                Label {
                    text: "ClipSnap Preferences"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#FFFFFF"
                }
            }

            // Section 1: Monitoring & Autostart
            Rectangle {
                Layout.fillWidth: true
                implicitHeight: col1.implicitHeight + 24
                radius: 6
                color: "#2D2D2D"
                border.color: "#3D3D3D"
                border.width: 1

                ColumnLayout {
                    id: col1
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 12

                    Label {
                        text: "Clipboard Monitoring & Startup"
                        font.pixelSize: 13
                        font.bold: true
                        color: "#E95420"
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label {
                            text: "Background Clipboard Capture"
                            color: "#FFFFFF"
                            Layout.fillWidth: true
                        }
                        Switch {
                            checked: settings.monitoringEnabled
                            onCheckedChanged: {
                                if (checked !== settings.monitoringEnabled) {
                                    if (checked) app.resumeMonitoring();
                                    else app.pauseMonitoring();
                                }
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label {
                            text: "Start Automatically on Login"
                            color: "#FFFFFF"
                            Layout.fillWidth: true
                        }
                        Switch {
                            checked: settings.autostartEnabled
                            onCheckedChanged: settings.autostartEnabled = checked
                        }
                    }
                }
            }

            // Section 2: Storage Limits
            Rectangle {
                Layout.fillWidth: true
                implicitHeight: col2.implicitHeight + 24
                radius: 6
                color: "#2D2D2D"
                border.color: "#3D3D3D"
                border.width: 1

                ColumnLayout {
                    id: col2
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 12

                    Label {
                        text: "History Storage Limits"
                        font.pixelSize: 13
                        font.bold: true
                        color: "#E95420"
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label {
                            text: "Retention Period (Days)"
                            color: "#FFFFFF"
                            Layout.fillWidth: true
                        }
                        SpinBox {
                            from: 1; to: 365; value: settings.retentionDays
                            onValueChanged: settings.retentionDays = value
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label {
                            text: "Maximum Stored Entries"
                            color: "#FFFFFF"
                            Layout.fillWidth: true
                        }
                        SpinBox {
                            from: 10; to: 5000; value: settings.maxHistoryEntries; stepSize: 50
                            onValueChanged: settings.maxHistoryEntries = value
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label {
                            text: "Storage Budget (MB)"
                            color: "#FFFFFF"
                            Layout.fillWidth: true
                        }
                        SpinBox {
                            from: 50; to: 5000; value: settings.maxStorageMb; stepSize: 50
                            onValueChanged: settings.maxStorageMb = value
                        }
                    }
                }
            }

            // Section 3: Keyboard Shortcuts
            Rectangle {
                Layout.fillWidth: true
                implicitHeight: col3.implicitHeight + 24
                radius: 6
                color: "#2D2D2D"
                border.color: "#3D3D3D"
                border.width: 1

                ColumnLayout {
                    id: col3
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    Label {
                        text: "Configured Desktop Shortcuts"
                        font.pixelSize: 13
                        font.bold: true
                        color: "#E95420"
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label { text: "Open History Window:"; color: "#AEA79F"; Layout.fillWidth: true }
                        Rectangle {
                            implicitWidth: 80; implicitHeight: 24; radius: 4; color: "#383838"
                            border.color: "#4A4A4A"; border.width: 1
                            Label { anchors.centerIn: parent; text: "Alt + H"; color: "#FFFFFF"; font.bold: true; font.pixelSize: 11 }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Label { text: "Capture Screenshot:"; color: "#AEA79F"; Layout.fillWidth: true }
                        Rectangle {
                            implicitWidth: 100; implicitHeight: 24; radius: 4; color: "#383838"
                            border.color: "#4A4A4A"; border.width: 1
                            Label { anchors.centerIn: parent; text: "Alt + Shift + S"; color: "#FFFFFF"; font.bold: true; font.pixelSize: 11 }
                        }
                    }
                }
            }

            // Close Button
            Button {
                id: closeBtn
                Layout.alignment: Qt.AlignRight
                text: "Close"
                
                contentItem: Text {
                    text: closeBtn.text
                    font.pixelSize: 12
                    font.bold: true
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    implicitWidth: 80
                    implicitHeight: 32
                    radius: 5
                    color: closeBtn.hovered ? "#383838" : "#2D2D2D"
                    border.color: "#4A4A4A"
                    border.width: 1
                }

                onClicked: settingsWindow.close()
            }
        }
    }
}
