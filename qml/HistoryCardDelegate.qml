import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: GridView.view ? GridView.view.cellWidth : 260
    height: GridView.view ? GridView.view.cellHeight : 224

    property var modelId: model.id
    property bool isCurrent: GridView.isCurrentItem

    signal restoreClicked()
    signal deleteClicked()
    signal pinClicked()

    property bool justCopied: false

    Timer {
        id: copyFeedbackTimer
        interval: 250
        repeat: false
        onTriggered: {
            root.justCopied = false
        }
    }

    function triggerCopy() {
        justCopied = true
        root.restoreClicked()
        copyFeedbackTimer.restart()
    }

    // Main Card Rectangle with margins for grid spacing
    Rectangle {
        id: cardRect
        anchors.fill: parent
        anchors.margins: 6
        radius: 8
        color: justCopied ? "#3E2518" : (root.isCurrent ? "#353535" : (cardMouseArea.containsMouse ? "#323232" : "#2A2A2A"))
        border.color: justCopied ? "#E95420" : (root.isCurrent ? "#E95420" : (cardMouseArea.containsMouse ? "#555555" : "#383838"))
        border.width: (root.isCurrent || justCopied) ? 2 : 1
        clip: true

        Behavior on color { ColorAnimation { duration: 120 } }
        Behavior on border.color { ColorAnimation { duration: 120 } }

        // Card Click Area (captures clicks on background and non-button elements)
        MouseArea {
            id: cardMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: root.triggerCopy()
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // Top Preview Section (Images or Code/Text Snippet)
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 112
                color: model.isImage ? "#1A1A1A" : "#1E1E1E"
                clip: true

                // Image Preview
                Image {
                    id: imgThumb
                    anchors.fill: parent
                    source: (model.isImage && model.thumbnailPath) ? ("file://" + model.thumbnailPath) : ""
                    fillMode: Image.PreserveAspectCrop
                    visible: model.isImage && model.thumbnailPath !== ""
                    cache: true
                    smooth: true

                    // Subtle hover zoom effect
                    scale: cardMouseArea.containsMouse ? 1.03 : 1.0
                    Behavior on scale { NumberAnimation { duration: 180 } }
                }

                // Fallback Image Placeholder
                Label {
                    anchors.centerIn: parent
                    text: "🖼️"
                    font.pixelSize: 34
                    visible: model.isImage && (!model.thumbnailPath || model.thumbnailPath === "")
                }

                // Text / Code Snippet Preview
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 6
                    color: "#181818"
                    radius: 4
                    visible: !model.isImage

                    Rectangle {
                        width: 3
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        color: "#E95420"
                        radius: 1.5
                    }

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.rightMargin: 8
                        anchors.topMargin: 8
                        anchors.bottomMargin: 8
                        text: model.displayText || ""
                        color: "#DDDDDD"
                        font.pixelSize: 11
                        font.family: "Ubuntu Mono, monospace, system-ui"
                        wrapMode: Text.WrapAnywhere
                        elide: Text.ElideRight
                        maximumLineCount: 5
                    }
                }

                // Top Right Origin / Type Badge
                Rectangle {
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.margins: 6
                    implicitWidth: originText.implicitWidth + 12
                    implicitHeight: 20
                    radius: 10
                    color: model.isImage ? "#8A000000" : "#2E2E2E"
                    border.color: model.isImage ? "#55FFFFFF" : "#444444"
                    border.width: 1

                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 4
                        Text {
                            text: model.isImage ? "🖼️" : "📄"
                            font.pixelSize: 9
                        }
                        Text {
                            id: originText
                            text: model.origin === "screenshot" ? "Screenshot" : (model.isImage ? "Image" : "Text")
                            color: "#FFFFFF"
                            font.pixelSize: 10
                            font.bold: true
                            font.family: "Ubuntu, system-ui, sans-serif"
                        }
                    }
                }

                // Top Left Pin Badge (if pinned)
                Rectangle {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 6
                    implicitWidth: 22
                    implicitHeight: 20
                    radius: 4
                    color: "#E95420"
                    visible: model.pinned

                    Text {
                        anchors.centerIn: parent
                        text: "📌"
                        font.pixelSize: 10
                    }
                }
            }

            // Divider
            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#383838"
            }

            // Bottom Content Section: Details & Quick Actions
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 8
                spacing: 5

                // 1-Line Text Summary
                Label {
                    Layout.fillWidth: true
                    text: model.isImage ? ("Screenshot " + (model.sizeStr || "")) : (model.displayText || "")
                    color: "#FFFFFF"
                    font.pixelSize: 12
                    font.bold: true
                    font.family: "Ubuntu, system-ui, sans-serif"
                    elide: Text.ElideRight
                    maximumLineCount: 1
                }

                // Metadata Row (Timestamp & Size)
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 6

                    Label {
                        text: model.timestamp || ""
                        color: "#AEA79F"
                        font.pixelSize: 11
                        font.family: "Ubuntu, system-ui, sans-serif"
                    }

                    Label {
                        text: "•"
                        color: "#555555"
                        font.pixelSize: 10
                    }

                    Rectangle {
                        implicitWidth: sizeLabel.implicitWidth + 8
                        implicitHeight: 18
                        radius: 3
                        color: "#222222"
                        border.color: "#3A3A3A"
                        border.width: 1

                        Label {
                            id: sizeLabel
                            anchors.centerIn: parent
                            text: model.sizeStr || ""
                            color: "#9E9E9E"
                            font.pixelSize: 10
                            font.family: "Ubuntu, system-ui, sans-serif"
                        }
                    }

                    Item { Layout.fillWidth: true }
                }

                // Action Buttons Row
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 6

                    // Large Copy Button
                    Button {
                        id: btnCopyAction
                        Layout.fillWidth: true
                        implicitHeight: 28

                        contentItem: RowLayout {
                            spacing: 4
                            anchors.centerIn: parent
                            Text {
                                text: root.justCopied ? "✓" : "📋"
                                font.pixelSize: 11
                            }
                            Text {
                                text: root.justCopied ? "Copied!" : "Copy"
                                font.pixelSize: 11
                                font.bold: true
                                font.family: "Ubuntu, system-ui, sans-serif"
                                color: "#FFFFFF"
                            }
                        }

                        background: Rectangle {
                            radius: 4
                            color: root.justCopied
                                   ? "#38B44A"
                                   : (btnCopyAction.down ? "#C34113" : (btnCopyAction.hovered ? "#FF6E38" : "#E95420"))
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: root.triggerCopy()
                        }
                    }

                    // Pin ToolButton
                    Button {
                        id: btnPin
                        implicitWidth: 28
                        implicitHeight: 28

                        contentItem: Text {
                            text: model.pinned ? "📌" : "📍"
                            font.pixelSize: 12
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 4
                            color: model.pinned ? "#3A2A1A" : (btnPin.hovered ? "#3E3E3E" : "#222222")
                            border.color: model.pinned ? "#E95420" : "#383838"
                            border.width: 1
                        }

                        ToolTip.text: model.pinned ? "Unpin item" : "Pin item to prevent deletion"
                        ToolTip.visible: btnPin.hovered
                        ToolTip.delay: 300

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: root.pinClicked()
                        }
                    }

                    // Delete ToolButton
                    Button {
                        id: btnDel
                        implicitWidth: 28
                        implicitHeight: 28

                        contentItem: Text {
                            text: "🗑"
                            font.pixelSize: 12
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 4
                            color: btnDel.hovered ? "#5A2320" : "#222222"
                            border.color: btnDel.hovered ? "#DF382C" : "#383838"
                            border.width: 1
                        }

                        ToolTip.text: "Delete this item"
                        ToolTip.visible: btnDel.hovered
                        ToolTip.delay: 300

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: root.deleteClicked()
                        }
                    }
                }
            }
        }

        // Copied Feedback Overlay
        Rectangle {
            anchors.fill: parent
            color: "#E6E95420"
            radius: 8
            visible: root.justCopied
            z: 99

            RowLayout {
                anchors.centerIn: parent
                spacing: 8
                Text {
                    text: "✓"
                    color: "#FFFFFF"
                    font.pixelSize: 22
                    font.bold: true
                }
                Text {
                    text: "Copied to Clipboard!"
                    color: "#FFFFFF"
                    font.pixelSize: 13
                    font.bold: true
                    font.family: "Ubuntu, system-ui, sans-serif"
                }
            }
        }
    }
}
