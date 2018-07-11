import QtQuick 2.4
import QtQuick.Controls 1.2

Item {
    visible: true
    height: 720
    width: 1280

    Item{
        id:menu
        anchors{
            left:parent.left
            right:parent.right
            top:parent.top
        }
        Rectangle{
            anchors.fill: parent
            color:"darkslategrey"
        }
        Text{
            text:qsTr("Qml Runtime Reload Example")
            anchors.centerIn: parent
            color:"white"
            font.pixelSize: 18
            font.weight: Font.DemiBold
        }

        height: parent.height *.08

    }
    Loader{
        id:contentLoader
        source:app.currentScreen
        anchors{
            top:menu.bottom
            left:parent.left
            right:parent.right
            bottom:parent.bottom
        }
    }
}
