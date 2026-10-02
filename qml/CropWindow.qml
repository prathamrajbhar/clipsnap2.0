import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

Window {
    id: cropWindow
    visible: false
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Window
    transientParent: null
    color: "#000000"
    width: Screen.width > 0 ? Screen.width : 1920
    height: Screen.height > 0 ? Screen.height : 1080
    x: Screen.virtualX
    y: Screen.virtualY

    property string imageUrl: ""
    property real selX: 0
    property real selY: 0
    property real selW: 0
    property real selH: 0
    property bool selectionActive: false
    property int dragMode: 0 // 0=none, 1=new selection, 2=move selection, 3=resize handle (TL, T, TR, R, BR, B, BL, L)
    property int resizeHandle: 0

    property real startMouseX: 0
    property real startMouseY: 0
    property real initialSelX: 0
    property real initialSelY: 0
    property real initialSelW: 0
    property real initialSelH: 0

    function showWithImage(img) {
        console.log("CropWindow showWithImage starting...")
        selectionActive = false
        selX = 0
        selY = 0
        selW = 0
        selH = 0
        dragMode = 0
        imageEditor.setImage(img)
        imageUrl = "image://editor/original?t=" + Date.now()
        cropWindow.x = Screen.virtualX
        cropWindow.y = Screen.virtualY
        cropWindow.width = Screen.width > 0 ? Screen.width : 1920
        cropWindow.height = Screen.height > 0 ? Screen.height : 1080
        cropWindow.visible = true
        cropWindow.show()
        cropWindow.raise()
        cropWindow.requestActivate()
        console.log("CropWindow showWithImage finished: visible =", cropWindow.visible, "x=", cropWindow.x, "y=", cropWindow.y, "w=", cropWindow.width, "h=", cropWindow.height)
    }

    function commitCropAndClose() {
        if (selectionActive && selW >= 4 && selH >= 4) {
            let nx = selX / width
            let ny = selY / height
            let nw = selW / width
            let nh = selH / height
            imageEditor.cropAndCopy(nx, ny, nw, nh)
        } else {
            imageEditor.copyFullScreen()
        }
        closeWindow()
    }

    function saveCropAndClose() {
        if (selectionActive && selW >= 4 && selH >= 4) {
            let nx = selX / width
            let ny = selY / height
            let nw = selW / width
            let nh = selH / height
            imageEditor.cropAndSave(nx, ny, nw, nh)
        } else {
            imageEditor.saveFullScreen()
        }
        closeWindow()
    }

    function copyFullScreenAndClose() {
        imageEditor.copyFullScreen()
        closeWindow()
    }

    function saveFullScreenAndClose() {
        imageEditor.saveFullScreen()
        closeWindow()
    }

    function cancelAndClose() {
        imageEditor.cancel()
        closeWindow()
    }

    function closeWindow() {
        selectionActive = false
        cropWindow.visible = false
        cropWindow.hide()
    }

    // Background: Frozen desktop screenshot
    Image {
        id: bgImage
        anchors.fill: parent
        source: cropWindow.imageUrl
        cache: false
        fillMode: Image.Stretch
        visible: cropWindow.imageUrl !== ""
    }

    // Spotlight Dim Mask: 4 rectangles surrounding the selection box
    Item {
        anchors.fill: parent
        visible: cropWindow.selectionActive

        // Top mask
        Rectangle {
            x: 0
            y: 0
            width: parent.width
            height: Math.max(0, cropWindow.selY)
            color: "#65000000"
        }
        // Bottom mask
        Rectangle {
            x: 0
            y: cropWindow.selY + cropWindow.selH
            width: parent.width
            height: Math.max(0, parent.height - (cropWindow.selY + cropWindow.selH))
            color: "#65000000"
        }
        // Left mask
        Rectangle {
            x: 0
            y: cropWindow.selY
            width: Math.max(0, cropWindow.selX)
            height: cropWindow.selH
            color: "#65000000"
        }
        // Right mask
        Rectangle {
            x: cropWindow.selX + cropWindow.selW
            y: cropWindow.selY
            width: Math.max(0, parent.width - (cropWindow.selX + cropWindow.selW))
            height: cropWindow.selH
            color: "#65000000"
        }
    }

    // Default uniform dim mask when no selection is active
    Rectangle {
        anchors.fill: parent
        color: "#50000000"
        visible: !cropWindow.selectionActive
    }

    // Global Canvas MouseArea
    MouseArea {
        id: mainMouseArea
        anchors.fill: parent
        cursorShape: cropWindow.selectionActive ? Qt.CrossCursor : Qt.CrossCursor
        hoverEnabled: true

        onPressed: (mouse) => {
            // Check if clicking inside the current selection to move it
            if (cropWindow.selectionActive &&
                mouse.x >= cropWindow.selX && mouse.x <= cropWindow.selX + cropWindow.selW &&
                mouse.y >= cropWindow.selY && mouse.y <= cropWindow.selY + cropWindow.selH) {
                cropWindow.dragMode = 2 // move
                cropWindow.startMouseX = mouse.x
                cropWindow.startMouseY = mouse.y
                cropWindow.initialSelX = cropWindow.selX
                cropWindow.initialSelY = cropWindow.selY
                return
            }

            // Otherwise start a new selection
            cropWindow.dragMode = 1 // new selection
            cropWindow.startMouseX = mouse.x
            cropWindow.startMouseY = mouse.y
            cropWindow.selX = mouse.x
            cropWindow.selY = mouse.y
            cropWindow.selW = 0
            cropWindow.selH = 0
            cropWindow.selectionActive = true
        }

        onPositionChanged: (mouse) => {
            if (cropWindow.dragMode === 1) { // dragging new selection
                let curX = Math.max(0, Math.min(width, mouse.x))
                let curY = Math.max(0, Math.min(height, mouse.y))

                cropWindow.selX = Math.min(cropWindow.startMouseX, curX)
                cropWindow.selY = Math.min(cropWindow.startMouseY, curY)
                cropWindow.selW = Math.abs(curX - cropWindow.startMouseX)
                cropWindow.selH = Math.abs(curY - cropWindow.startMouseY)
            } else if (cropWindow.dragMode === 2) { // moving selection
                let dx = mouse.x - cropWindow.startMouseX
                let dy = mouse.y - cropWindow.startMouseY
                let newX = Math.max(0, Math.min(width - cropWindow.selW, cropWindow.initialSelX + dx))
                let newY = Math.max(0, Math.min(height - cropWindow.selH, cropWindow.initialSelY + dy))
                cropWindow.selX = newX
                cropWindow.selY = newY
            } else if (cropWindow.dragMode === 3) { // resizing handle
                handleResize(mouse.x, mouse.y)
            }
        }

        onReleased: (mouse) => {
            cropWindow.dragMode = 0
            if (cropWindow.selW < 8 || cropWindow.selH < 8) {
                cropWindow.selectionActive = false
                cropWindow.selW = 0
                cropWindow.selH = 0
            }
        }

        onDoubleClicked: (mouse) => {
            if (cropWindow.selectionActive &&
                mouse.x >= cropWindow.selX && mouse.x <= cropWindow.selX + cropWindow.selW &&
                mouse.y >= cropWindow.selY && mouse.y <= cropWindow.selY + cropWindow.selH) {
                commitCropAndClose()
            }
        }
    }

    // Helper function for 8-direction handle resizing
    function handleResize(curX, curY) {
        let x = Math.max(0, Math.min(width, curX))
        let y = Math.max(0, Math.min(height, curY))
        let dx = x - startMouseX
        let dy = y - startMouseY

        switch (resizeHandle) {
        case 1: // Top-Left
            selX = Math.min(initialSelX + dx, initialSelX + initialSelW - 8)
            selY = Math.min(initialSelY + dy, initialSelY + initialSelH - 8)
            selW = initialSelW - (selX - initialSelX)
            selH = initialSelH - (selY - initialSelY)
            break
        case 2: // Top
            selY = Math.min(initialSelY + dy, initialSelY + initialSelH - 8)
            selH = initialSelH - (selY - initialSelY)
            break
        case 3: // Top-Right
            selW = Math.max(8, initialSelW + dx)
            selY = Math.min(initialSelY + dy, initialSelY + initialSelH - 8)
            selH = initialSelH - (selY - initialSelY)
            break
        case 4: // Right
            selW = Math.max(8, initialSelW + dx)
            break
        case 5: // Bottom-Right
            selW = Math.max(8, initialSelW + dx)
            selH = Math.max(8, initialSelH + dy)
            break
        case 6: // Bottom
            selH = Math.max(8, initialSelH + dy)
            break
        case 7: // Bottom-Left
            selX = Math.min(initialSelX + dx, initialSelX + initialSelW - 8)
            selW = initialSelW - (selX - initialSelX)
            selH = Math.max(8, initialSelH + dy)
            break
        case 8: // Left
            selX = Math.min(initialSelX + dx, initialSelX + initialSelW - 8)
            selW = initialSelW - (selX - initialSelX)
            break
        }
    }

    // Selection Box Overlay
    Rectangle {
        id: selectionBox
        visible: cropWindow.selectionActive && cropWindow.selW > 0 && cropWindow.selH > 0
        x: cropWindow.selX
        y: cropWindow.selY
        width: cropWindow.selW
        height: cropWindow.selH
        color: "transparent"
        border.color: "#E95420" // Canonical Ubuntu Orange
        border.width: 2

        // Inner drag cursor
        MouseArea {
            anchors.fill: parent
            anchors.margins: 10
            cursorShape: Qt.SizeAllCursor
            hoverEnabled: true
            onPressed: (mouse) => {
                cropWindow.dragMode = 2
                cropWindow.startMouseX = mouse.x + selectionBox.x
                cropWindow.startMouseY = mouse.y + selectionBox.y
                cropWindow.initialSelX = cropWindow.selX
                cropWindow.initialSelY = cropWindow.selY
            }
            onPositionChanged: (mouse) => {
                if (cropWindow.dragMode === 2) {
                    let curX = mouse.x + selectionBox.x
                    let curY = mouse.y + selectionBox.y
                    let dx = curX - cropWindow.startMouseX
                    let dy = curY - cropWindow.startMouseY
                    cropWindow.selX = Math.max(0, Math.min(cropWindow.width - cropWindow.selW, cropWindow.initialSelX + dx))
                    cropWindow.selY = Math.max(0, Math.min(cropWindow.height - cropWindow.selH, cropWindow.initialSelY + dy))
                }
            }
            onReleased: cropWindow.dragMode = 0
            onDoubleClicked: commitCropAndClose()
        }

        // Dimension Pill Badge
        Rectangle {
            id: dimBadge
            anchors.bottom: (parent.y < 30) ? undefined : parent.top
            anchors.top: (parent.y < 30) ? parent.top : undefined
            anchors.left: parent.left
            anchors.bottomMargin: 6
            anchors.topMargin: (parent.y < 30) ? 6 : 0
            anchors.leftMargin: (parent.y < 30) ? 6 : 0
            implicitWidth: dimLabel.implicitWidth + 14
            implicitHeight: 22
            radius: 4
            color: "#E95420"
            visible: parent.width >= 40 && parent.height >= 25

            Label {
                id: dimLabel
                anchors.centerIn: parent
                text: Math.round(cropWindow.selW) + " × " + Math.round(cropWindow.selH) + " px"
                color: "#FFFFFF"
                font.pixelSize: 11
                font.bold: true
                font.family: "Ubuntu, system-ui, sans-serif"
            }
        }

        // 8 Resize Handles
        Repeater {
            model: [
                { id: 1, ax: 0.0, ay: 0.0, cursor: Qt.SizeFDiagCursor }, // Top-Left
                { id: 2, ax: 0.5, ay: 0.0, cursor: Qt.SizeVerCursor },   // Top
                { id: 3, ax: 1.0, ay: 0.0, cursor: Qt.SizeBDiagCursor }, // Top-Right
                { id: 4, ax: 1.0, ay: 0.5, cursor: Qt.SizeHorCursor },   // Right
                { id: 5, ax: 1.0, ay: 1.0, cursor: Qt.SizeFDiagCursor }, // Bottom-Right
                { id: 6, ax: 0.5, ay: 1.0, cursor: Qt.SizeVerCursor },   // Bottom
                { id: 7, ax: 0.0, ay: 1.0, cursor: Qt.SizeBDiagCursor }, // Bottom-Left
                { id: 8, ax: 0.0, ay: 0.5, cursor: Qt.SizeHorCursor }    // Left
            ]

            Rectangle {
                id: handleRect
                width: 9
                height: 9
                radius: 2
                color: "#FFFFFF"
                border.color: "#E95420"
                border.width: 2
                x: modelData.ax * parent.width - 4.5
                y: modelData.ay * parent.height - 4.5
                visible: parent.width >= 40 && parent.height >= 40

                MouseArea {
                    anchors.fill: parent
                    anchors.margins: -4
                    cursorShape: modelData.cursor
                    hoverEnabled: true
                    onPressed: (mouse) => {
                        cropWindow.dragMode = 3
                        cropWindow.resizeHandle = modelData.id
                        cropWindow.startMouseX = mouse.x + handleRect.x + selectionBox.x
                        cropWindow.startMouseY = mouse.y + handleRect.y + selectionBox.y
                        cropWindow.initialSelX = cropWindow.selX
                        cropWindow.initialSelY = cropWindow.selY
                        cropWindow.initialSelW = cropWindow.selW
                        cropWindow.initialSelH = cropWindow.selH
                    }
                    onPositionChanged: (mouse) => {
                        if (cropWindow.dragMode === 3) {
                            let curX = mouse.x + handleRect.x + selectionBox.x
                            let curY = mouse.y + handleRect.y + selectionBox.y
                            handleResize(curX, curY)
                        }
                    }
                    onReleased: cropWindow.dragMode = 0
                }
            }
        }
    }

    // Floating Action Bar anchored to the selection
    Rectangle {
        id: actionBar
        visible: cropWindow.selectionActive && cropWindow.selW >= 35 && cropWindow.selH >= 30 && cropWindow.dragMode === 0
        implicitWidth: actionRow.implicitWidth + 20
        implicitHeight: 40
        radius: 6
        color: "#1E1E1E" // Yaru Header/Toolbar Surface
        border.color: "#3D3D3D"
        border.width: 1

        // Position directly below or above selection box
        x: Math.max(12, Math.min(cropWindow.width - width - 12, cropWindow.selX + (cropWindow.selW - width) / 2))
        y: {
            if (cropWindow.selY + cropWindow.selH + 50 <= cropWindow.height) {
                return cropWindow.selY + cropWindow.selH + 10
            } else if (cropWindow.selY - 50 >= 0) {
                return cropWindow.selY - 50
            } else {
                return cropWindow.selY + 10
            }
        }

        RowLayout {
            id: actionRow
            anchors.centerIn: parent
            spacing: 8

            // Copy & Close Button (Primary Ubuntu Orange)
            Button {
                id: btnCopy
                contentItem: RowLayout {
                    spacing: 6
                    Text { text: "📋"; font.pixelSize: 13 }
                    Text {
                        text: "Copy (Enter)"
                        font.pixelSize: 12
                        font.bold: true
                        font.family: "Ubuntu, system-ui, sans-serif"
                        color: "#FFFFFF"
                    }
                }
                background: Rectangle {
                    implicitWidth: 105
                    implicitHeight: 28
                    radius: 4
                    color: btnCopy.down ? "#C34113" : (btnCopy.hovered ? "#FF6E38" : "#E95420")
                }
                onClicked: commitCropAndClose()
            }

            // Save to File Button
            Button {
                id: btnSave
                contentItem: RowLayout {
                    spacing: 6
                    Text { text: "💾"; font.pixelSize: 13 }
                    Text {
                        text: "Save (Ctrl+S)"
                        font.pixelSize: 12
                        font.family: "Ubuntu, system-ui, sans-serif"
                        color: "#FFFFFF"
                    }
                }
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 28
                    radius: 4
                    color: btnSave.hovered ? "#383838" : "#2A2A2A"
                    border.color: btnSave.hovered ? "#E95420" : "#404040"
                    border.width: 1
                }
                onClicked: saveCropAndClose()
            }

            Rectangle { width: 1; height: 18; color: "#3D3D3D" }

            // Cancel Button
            Button {
                id: btnCancel
                contentItem: Text {
                    text: "✕ Cancel (Esc)"
                    font.pixelSize: 12
                    font.family: "Ubuntu, system-ui, sans-serif"
                    color: btnCancel.hovered ? "#DF382C" : "#AEA79F"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    implicitWidth: 90
                    implicitHeight: 28
                    radius: 4
                    color: btnCancel.hovered ? "#383838" : "transparent"
                }
                onClicked: cancelAndClose()
            }
        }
    }

    // Top Instruction Capsule Pill
    Rectangle {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 24
        implicitWidth: hintRow.implicitWidth + 28
        implicitHeight: 36
        radius: 18
        color: "#242424" // Ubuntu Base Dark
        border.color: "#3D3D3D"
        border.width: 1
        opacity: cropWindow.dragMode !== 0 ? 0.25 : 0.95

        Behavior on opacity { NumberAnimation { duration: 150 } }

        RowLayout {
            id: hintRow
            anchors.centerIn: parent
            spacing: 12

            Label {
                text: "🖱️ Drag to select area"
                color: "#FFFFFF"
                font.pixelSize: 12
                font.bold: true
                font.family: "Ubuntu, system-ui, sans-serif"
            }

            Rectangle { width: 1; height: 14; color: "#484848" }

            Label {
                text: "↵ Enter: Copy"
                color: "#E95420"
                font.pixelSize: 12
                font.bold: true
                font.family: "Ubuntu, system-ui, sans-serif"
            }

            Rectangle { width: 1; height: 14; color: "#484848" }

            Label {
                text: "💾 Ctrl+S: Save"
                color: "#AEA79F"
                font.pixelSize: 12
                font.family: "Ubuntu, system-ui, sans-serif"
            }

            Rectangle { width: 1; height: 14; color: "#484848" }

            Label {
                text: "⎋ Esc: Cancel"
                color: "#AEA79F"
                font.pixelSize: 12
                font.family: "Ubuntu, system-ui, sans-serif"
            }
        }
    }

    // Global Keyboard Shortcuts
    Shortcut {
        sequence: "Escape"
        onActivated: cancelAndClose()
    }

    Shortcut {
        sequence: "Return"
        onActivated: commitCropAndClose()
    }

    Shortcut {
        sequence: "Enter"
        onActivated: commitCropAndClose()
    }

    Shortcut {
        sequences: ["Ctrl+C", "Ctrl+Ins"]
        onActivated: commitCropAndClose()
    }

    Shortcut {
        sequence: "Ctrl+S"
        onActivated: saveCropAndClose()
    }
}
