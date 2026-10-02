import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    function copyAndDismiss(itemId) {
        historyModel.restoreItem(itemId)
        hideAfterCopyTimer.restart()
    }

    Timer {
        id: hideAfterCopyTimer
        interval: 220
        repeat: false
        onTriggered: {
            if (root.Window && root.Window.window) {
                root.Window.window.hide()
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        // Top Search Bar
        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "🔍  Search clipboard history (text, snippets, image names)..."
                font.pixelSize: 13
                font.family: "Ubuntu, system-ui, sans-serif"
                color: "#FFFFFF"
                placeholderTextColor: "#8E8E8E"
                leftPadding: 14
                rightPadding: 32

                background: Rectangle {
                    implicitHeight: 38
                    color: "#2C2C2C"
                    radius: 6
                    border.color: searchField.activeFocus ? "#E95420" : "#404040"
                    border.width: searchField.activeFocus ? 2 : 1
                }

                Keys.onEscapePressed: {
                    if (root.Window && root.Window.window) {
                        root.Window.window.hide()
                    }
                }
                Keys.onDownPressed: {
                    if (gridView.count > 0) {
                        gridView.forceActiveFocus()
                        if (gridView.currentIndex < 0) gridView.currentIndex = 0
                    }
                }
                Keys.onReturnPressed: {
                    if (gridView.count > 0) {
                        if (gridView.currentIndex < 0) gridView.currentIndex = 0
                        let item = gridView.currentItem
                        if (item) {
                            root.copyAndDismiss(item.modelId)
                        }
                    }
                }
                onTextChanged: historyModel.search(text, filterBar.currentFilter)

                // Clear button
                ToolButton {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 4
                    text: "✕"
                    visible: searchField.text.length > 0
                    onClicked: {
                        searchField.text = ""
                        searchField.forceActiveFocus()
                    }
                }
            }
        }

        // Filter Bar (Tabs + Delete All + Screenshot Button)
        FilterBar {
            id: filterBar
            Layout.fillWidth: true
            onCurrentFilterChanged: historyModel.search(searchField.text, currentFilter)
            onClearAllClicked: clearConfirmDialog.open()
        }

        // Main Content Area: Responsive Card Grid or Empty State
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridView {
                id: gridView
                anchors.fill: parent
                model: historyModel
                clip: true
                focus: true
                boundsBehavior: Flickable.StopAtBounds

                // Responsive card sizing: automatically fills rows with ~260px wide cards
                cellWidth: Math.floor(width / Math.max(1, Math.floor(width / 260)))
                cellHeight: 224

                delegate: HistoryCardDelegate {
                    onRestoreClicked: root.copyAndDismiss(model.id)
                    onDeleteClicked: historyModel.deleteItem(model.id)
                    onPinClicked: historyModel.togglePin(model.id)
                }

                Keys.onReturnPressed: {
                    if (currentIndex >= 0 && currentItem) {
                        root.copyAndDismiss(currentItem.modelId)
                    }
                }
                Keys.onDeletePressed: {
                    if (currentIndex >= 0 && currentItem) {
                        historyModel.deleteItem(currentItem.modelId)
                    }
                }
                Keys.onUpPressed: {
                    let cols = Math.max(1, Math.floor(width / cellWidth))
                    if (currentIndex < cols) {
                        searchField.forceActiveFocus()
                    } else {
                        currentIndex = Math.max(0, currentIndex - cols)
                    }
                }
                Keys.onEscapePressed: {
                    if (root.Window && root.Window.window) {
                        root.Window.window.hide()
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    id: vbar
                    active: true
                    policy: ScrollBar.AsNeeded
                    contentItem: Rectangle {
                        implicitWidth: 6
                        radius: 3
                        color: "#5E5E5E"
                    }
                }
            }

            // Empty State Display
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 12
                visible: gridView.count === 0

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: searchField.text.length > 0 ? "🔎" : "📋"
                    font.pixelSize: 48
                }

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: searchField.text.length > 0 ? "No matching history found" : "Clipboard History is Empty"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#FFFFFF"
                    font.family: "Ubuntu, system-ui, sans-serif"
                }

                Label {
                    Layout.alignment: Qt.AlignHCenter
                    text: searchField.text.length > 0
                          ? "Try searching for a different keyword or change the filter tab."
                          : "Copied text and screenshots (Alt+Shift+S) will appear here as cards automatically."
                    font.pixelSize: 12
                    color: "#AEA79F"
                    font.family: "Ubuntu, system-ui, sans-serif"
                }
            }
        }

        // Bottom Status Bar
        StatusBar {
            Layout.fillWidth: true
        }
    }

    // Ubuntu-themed Confirmation Dialog for Delete All
    Popup {
        id: clearConfirmDialog
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        width: Math.min(460, root.width - 40)
        padding: 0

        Overlay.modal: Rectangle {
            color: "#99000000"
        }

        background: Rectangle {
            color: "#282828"
            radius: 8
            border.color: "#DF382C"
            border.width: 1
        }

        contentItem: ColumnLayout {
            spacing: 16
            Layout.fillWidth: true

            // Header Banner
            Rectangle {
                Layout.fillWidth: true
                implicitHeight: 46
                color: "#351C1A"
                radius: 8

                // Flatten bottom corners
                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 8
                    color: "#351C1A"
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16
                    spacing: 10

                    Label {
                        text: "⚠️"
                        font.pixelSize: 18
                    }
                    Label {
                        text: "Clear Clipboard History"
                        color: "#FFFFFF"
                        font.pixelSize: 15
                        font.bold: true
                        font.family: "Ubuntu, system-ui, sans-serif"
                    }
                }
            }

            // Description Body
            ColumnLayout {
                Layout.fillWidth: true
                Layout.leftMargin: 18
                Layout.rightMargin: 18
                spacing: 8

                Label {
                    Layout.fillWidth: true
                    text: "How would you like to clear the clipboard history?"
                    color: "#DDDDDD"
                    font.pixelSize: 13
                    wrapMode: Text.Wrap
                    font.family: "Ubuntu, system-ui, sans-serif"
                }

                Label {
                    Layout.fillWidth: true
                    text: "You can keep your pinned items safe while removing the rest, or permanently wipe all entries."
                    color: "#AEA79F"
                    font.pixelSize: 11
                    wrapMode: Text.Wrap
                    font.family: "Ubuntu, system-ui, sans-serif"
                }
            }

            // Action Buttons
            RowLayout {
                Layout.fillWidth: true
                Layout.leftMargin: 18
                Layout.rightMargin: 18
                Layout.bottomMargin: 18
                spacing: 8

                // Cancel Button
                Button {
                    id: btnCancel
                    text: "Cancel"
                    Layout.preferredHeight: 32

                    contentItem: Text {
                        text: "Cancel"
                        color: "#DDDDDD"
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.family: "Ubuntu, system-ui, sans-serif"
                    }

                    background: Rectangle {
                        radius: 5
                        color: btnCancel.hovered ? "#454545" : "#353535"
                        border.color: "#505050"
                        border.width: 1
                    }

                    onClicked: clearConfirmDialog.close()
                }

                Item { Layout.fillWidth: true }

                // Clear Unpinned Button
                Button {
                    id: btnClearUnpinned
                    text: "Keep Pinned (Clear Others)"
                    Layout.preferredHeight: 32

                    contentItem: Text {
                        text: "Keep Pinned"
                        color: "#FFFFFF"
                        font.pixelSize: 12
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.family: "Ubuntu, system-ui, sans-serif"
                    }

                    background: Rectangle {
                        radius: 5
                        color: btnClearUnpinned.hovered ? "#FF6E38" : "#E95420"
                    }

                    ToolTip.text: "Clear all history except pinned items"
                    ToolTip.visible: btnClearUnpinned.hovered
                    ToolTip.delay: 300

                    onClicked: {
                        historyModel.clearUnpinned()
                        clearConfirmDialog.close()
                    }
                }

                // Delete All Button
                Button {
                    id: btnClearAll
                    text: "Delete All"
                    Layout.preferredHeight: 32

                    contentItem: Text {
                        text: "Delete All"
                        color: "#FFFFFF"
                        font.pixelSize: 12
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.family: "Ubuntu, system-ui, sans-serif"
                    }

                    background: Rectangle {
                        radius: 5
                        color: btnClearAll.hovered ? "#FF5244" : "#DF382C"
                    }

                    ToolTip.text: "Delete all history items including pinned"
                    ToolTip.visible: btnClearAll.hovered
                    ToolTip.delay: 300

                    onClicked: {
                        historyModel.clearAll()
                        clearConfirmDialog.close()
                    }
                }
            }
        }
    }

    Component.onCompleted: searchField.forceActiveFocus()
}
