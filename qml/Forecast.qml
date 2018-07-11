import QtQuick 2.0

Rectangle {
    id:forcastRoot
    anchors.fill: parent
    color:"green"



    Row{
        width: parent.width
        height: parent.height*.75
        spacing:forcastRoot.width *.01
        Repeater{

            model: 6
            delegate: Rectangle{
                color: "white"
                width: forcastRoot.width / 8
                height: parent.height
                Text {

                    text: app.dayOfWeek(index)
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: app.currentScreen = "Home.qml"
                }
            }
        }
    }

}

