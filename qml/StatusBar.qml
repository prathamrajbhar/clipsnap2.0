import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    height: 32

    Rectangle {
        anchors.fill: parent
        color: "#1E1E1E"
        radius: 6
        border.color: "#383838"
        border.width: 1

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 8
            spacing: 12

            // Interactive Monitoring Status Pill
            MouseArea {
                id: statusArea
                implicitWidth: statusRow.implicitWidth + 16
                implicitHeight: 22
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true

                Rectangle {
                    anchors.fill: parent
                    radius: 11
                    color: app.monitoringActive
                           ? (statusArea.containsMouse ? "#1D4726" : "#17361D")
                           : (statusArea.containsMouse ? "#5A2320" : "#3B1816")
                    border.color: app.monitoringActive ? "#38B44A" : "#DF382C"
                    border.width: 1

                    RowLayout {
                        id: statusRow
                        anchors.centerIn: parent
                        spacing: 6

                        Rectangle {
                            width: 7
                            height: 7
                            radius: 3.5
                            color: app.monitoringActive ? "#38B44A" : "#DF382C"
                        }

                        Label {
                            text: app.monitoringActive ? "Monitoring Active" : "Monitoring Paused"
                            color: app.monitoringActive ? "#8FE39B" : "#F4A09B"
                            font.pixelSize: 11
                            font.bold: true
                        }
                    }
                }

                onClicked: app.toggleMonitoring()

                ToolTip.text: app.monitoringActive ? "Click to pause clipboard capture" : "Click to resume clipboard capture"
                ToolTip.visible: statusArea.containsMouse
                ToolTip.delay: 300
            }

            // Keyboard Shortcuts Reference
            Label {
                text: "⌨  Alt+H: History  •  Alt+Shift+S: Screenshot"
                color: "#7A7A7A"
                font.pixelSize: 11
            }

            Item { Layout.fillWidth: true }

            // Item Count
            Label {
                text: historyModel.itemCount + (historyModel.itemCount === 1 ? " entry" : " entries")
                color: "#AEA79F"
                font.pixelSize: 11
                font.bold: true
            }

            // Settings Button
            ToolButton {
                id: settingsBtn
                implicitWidth: 26
                implicitHeight: 26
                text: "⚙"
                font.pixelSize: 14

                background: Rectangle {
                    radius: 4
                    color: settingsBtn.hovered ? "#383838" : "transparent"
                }

                onClicked: app.openSettings()

                ToolTip.text: "Open Settings"
                ToolTip.visible: settingsBtn.hovered
                ToolTip.delay: 300
            }
        }
    }
}
