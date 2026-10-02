import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ItemDelegate {
    id: root
    height: 74
    width: ListView.view ? ListView.view.width : 400

    property var modelId: model.id

    signal restoreClicked()
    signal deleteClicked()
    signal pinClicked()

    background: Rectangle {
        radius: 6
        color: root.ListView.isCurrentItem ? "#3A3A3A" : (root.hovered ? "#333333" : "#2B2B2B")
        border.color: root.ListView.isCurrentItem ? "#E95420" : (root.hovered ? "#4A4A4A" : "#363636")
        border.width: root.ListView.isCurrentItem ? 2 : 1

        Behavior on color { ColorAnimation { duration: 120 } }
        Behavior on border.color { ColorAnimation { duration: 120 } }

        // Left accent indicator on hover / selection
        Rectangle {
            width: 3
            height: parent.height - 12
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            radius: 1.5
            color: "#E95420"
            visible: root.ListView.isCurrentItem || root.hovered
        }
    }

    contentItem: RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 12

        // Left Icon / Thumbnail Box
        Rectangle {
            Layout.preferredWidth: 50
            Layout.preferredHeight: 50
            radius: 5
            color: model.isImage ? "#1E1E1E" : "#383838"
            border.color: "#484848"
            border.width: 1
            clip: true

            Image {
                anchors.fill: parent
                anchors.margins: 2
                source: (model.isImage && model.thumbnailPath) ? ("file://" + model.thumbnailPath) : ""
                fillMode: Image.PreserveAspectCrop
                visible: model.isImage && model.thumbnailPath !== ""
                cache: true
            }

            Label {
                anchors.centerIn: parent
                text: model.isImage ? "🖼" : "Aa"
                color: model.isImage ? "#E95420" : "#AEA79F"
                font.pixelSize: model.isImage ? 20 : 16
                font.bold: true
                visible: !model.isImage || model.thumbnailPath === ""
            }

            // Pinned badge on thumbnail
            Rectangle {
                anchors.top: parent.top
                anchors.right: parent.right
                width: 16
                height: 16
                radius: 3
                color: "#E95420"
                visible: model.pinned

                Text {
                    anchors.centerIn: parent
                    text: "📌"
                    font.pixelSize: 9
                }
            }
        }

        // Center Details (Text / Timestamp / Size)
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Label {
                Layout.fillWidth: true
                text: model.displayText || ""
                color: "#FFFFFF"
                font.pixelSize: 13
                font.family: "Ubuntu, system-ui, sans-serif"
                elide: Text.ElideRight
                maximumLineCount: 2
                wrapMode: Text.WordWrap
            }

            RowLayout {
                spacing: 8

                Label {
                    text: model.timestamp || ""
                    color: "#AEA79F"
                    font.pixelSize: 11
                }

                Label {
                    text: "•"
                    color: "#5E5E5E"
                    font.pixelSize: 11
                }

                Label {
                    text: model.sizeStr || ""
                    color: "#8E8E8E"
                    font.pixelSize: 11
                }

                Label {
                    text: model.origin === "clipboard" ? "[Clipboard]" : "[Screenshot]"
                    color: "#77216F"
                    font.pixelSize: 10
                    font.bold: true
                    visible: model.origin !== ""
                }
            }
        }

        // Action Buttons
        RowLayout {
            spacing: 6
            visible: root.hovered || root.ListView.isCurrentItem

            // Pin / Unpin Button
            ToolButton {
                id: pinBtn
                implicitWidth: 32
                implicitHeight: 32
                text: model.pinned ? "📌" : "📍"
                
                background: Rectangle {
                    radius: 4
                    color: pinBtn.hovered ? "#484848" : "transparent"
                }

                ToolTip.text: model.pinned ? "Unpin item" : "Pin to keep permanently"
                ToolTip.visible: pinBtn.hovered
                ToolTip.delay: 300

                onClicked: root.pinClicked()
            }

            // Delete Button
            ToolButton {
                id: delBtn
                implicitWidth: 32
                implicitHeight: 32
                text: "🗑"
                
                background: Rectangle {
                    radius: 4
                    color: delBtn.hovered ? "#5A2320" : "transparent"
                }

                ToolTip.text: "Delete item"
                ToolTip.visible: delBtn.hovered
                ToolTip.delay: 300

                onClicked: root.deleteClicked()
            }

            // Copy & Restore Button
            Button {
                id: restoreBtn
                text: "Copy"
                
                contentItem: Text {
                    text: restoreBtn.text
                    font.pixelSize: 11
                    font.bold: true
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    implicitHeight: 28
                    implicitWidth: 60
                    radius: 4
                    color: restoreBtn.down ? "#C34113" : (restoreBtn.hovered ? "#FF6E38" : "#E95420")
                }

                onClicked: root.restoreClicked()

                ToolTip.text: "Restore to clipboard & exit (Enter)"
                ToolTip.visible: restoreBtn.hovered
                ToolTip.delay: 300
            }
        }
    }

    onDoubleClicked: root.restoreClicked()
}
