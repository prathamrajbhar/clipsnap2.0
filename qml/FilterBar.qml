import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    height: 40
    property string currentFilter: "all"
    signal clearAllClicked()
    
    RowLayout {
        anchors.fill: parent
        spacing: 6
        
        Repeater {
            model: [
                { label: "All Items", filter: "all", icon: "📋" },
                { label: "Text", filter: "text", icon: "📄" },
                { label: "Images", filter: "images", icon: "🖼️" },
                { label: "Pinned", filter: "pinned", icon: "📌" }
            ]
            
            delegate: Button {
                id: tabBtn
                text: modelData.icon + "  " + modelData.label
                flat: true
                
                contentItem: Text {
                    text: tabBtn.text
                    font.pixelSize: 12
                    font.bold: root.currentFilter === modelData.filter
                    color: root.currentFilter === modelData.filter ? "#FFFFFF" : (tabBtn.hovered ? "#FFFFFF" : "#AEA79F")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                background: Rectangle {
                    implicitHeight: 32
                    radius: 5
                    color: root.currentFilter === modelData.filter ? "#E95420" : (tabBtn.hovered ? "#383838" : "transparent")
                    border.color: root.currentFilter === modelData.filter ? "#FF6E38" : (tabBtn.hovered ? "#484848" : "transparent")
                    border.width: 1
                }
                
                onClicked: root.currentFilter = modelData.filter
            }
        }
        
        Item { Layout.fillWidth: true }

        // Delete All Button
        Button {
            id: clearBtn
            text: "🗑  Delete All"
            enabled: historyModel.itemCount > 0
            opacity: enabled ? 1.0 : 0.45
            
            contentItem: Text {
                text: clearBtn.text
                font.pixelSize: 12
                font.bold: true
                color: clearBtn.enabled ? (clearBtn.hovered ? "#FF8888" : "#AEA79F") : "#666666"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            
            background: Rectangle {
                implicitHeight: 32
                implicitWidth: 105
                radius: 5
                color: clearBtn.down ? "#451815" : (clearBtn.hovered ? "#3B1816" : "#222222")
                border.color: (clearBtn.enabled && clearBtn.hovered) ? "#DF382C" : "#3D3D3D"
                border.width: 1
            }
            
            onClicked: root.clearAllClicked()
            
            ToolTip.text: "Clear all clipboard history"
            ToolTip.visible: clearBtn.hovered && clearBtn.enabled
            ToolTip.delay: 300
        }
        
        // Take Screenshot Button
        Button {
            id: captureBtn
            text: "📸  Take Screenshot"
            
            contentItem: Text {
                text: captureBtn.text
                font.pixelSize: 12
                font.bold: true
                color: "#FFFFFF"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            
            background: Rectangle {
                implicitHeight: 32
                implicitWidth: 145
                radius: 5
                color: captureBtn.down ? "#C34113" : (captureBtn.hovered ? "#FF6E38" : "#E95420")
                border.color: "#FFA07A"
                border.width: captureBtn.hovered ? 1 : 0
            }
            
            onClicked: app.requestCapture()
            
            ToolTip.text: "Capture screen region (Alt+Shift+S)"
            ToolTip.visible: captureBtn.hovered
            ToolTip.delay: 400
        }
    }
}
