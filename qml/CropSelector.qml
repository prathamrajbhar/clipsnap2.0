import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    
    signal cropConfirmed(rect selection)
    signal cancelled()
    
    function setImage(img) {} // placeholder, image already shown by CropWindow
    
    property real startX: 0
    property real startY: 0
    property real endX: 0
    property real endY: 0
    property bool isDragging: false
    
    property rect selectionRect: Qt.rect(
        Math.min(startX, endX),
        Math.min(startY, endY),
        Math.abs(endX - startX),
        Math.abs(endY - startY)
    )
    
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.CrossCursor
        
        onPressed: (mouse) => {
            root.startX = mouse.x
            root.startY = mouse.y
            root.endX = mouse.x
            root.endY = mouse.y
            root.isDragging = true
        }
        
        onPositionChanged: (mouse) => {
            if (root.isDragging) {
                root.endX = mouse.x
                root.endY = mouse.y
            }
        }
        
        onReleased: {
            root.isDragging = false
        }
    }
    
    // Selection rectangle
    Rectangle {
        x: root.selectionRect.x
        y: root.selectionRect.y
        width: root.selectionRect.width
        height: root.selectionRect.height
        color: "transparent"
        border.color: "#89b4fa"
        border.width: 2
        visible: root.selectionRect.width > 4 && root.selectionRect.height > 4
        
        // Size display
        Label {
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 4
            text: Math.round(root.selectionRect.width) + " × " + Math.round(root.selectionRect.height)
            color: "white"
            font.pixelSize: 12
            background: Rectangle { color: "#80000000"; radius: 3 }
            leftPadding: 4; rightPadding: 4
        }
    }
    
    Keys.onReturnPressed: {
        if (root.selectionRect.width > 4 && root.selectionRect.height > 4) {
            root.cropConfirmed(root.selectionRect)
        }
    }
    Keys.onEnterPressed: { Keys.onReturnPressed(event) }
    Keys.onEscapePressed: root.cancelled()
    
    focus: true
}
