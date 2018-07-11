import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    visible: true
    height:720; width:1280
    Rectangle{
        anchors.fill: menu
        color: "lightblue"
    }

    RowLayout{
        id:menu
        anchors {
            left:parent.left
            right:parent.right
            top:parent.top
        }
        height: parent.height *.08
        Label {
            Layout.fillWidth: true
            Layout.fillHeight: true
            verticalAlignment: Text.AlignVCenter
            id: name
            text: qsTr("This set of qml uses QtQuickControls and QtQuickLayouts")
            font.pointSize: 18
        }

        Button{
            text:qsTr("Reload")
            onClicked: app.reload()
        }

        Button{
            text:qsTr("Set Default Skin")
            onClicked: app.currentSkinEntry = ""
        }

        Button{
            text:qsTr("Use Window")
            onClicked: app.usingWindow = true
        }

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
