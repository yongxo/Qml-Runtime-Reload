import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
Item {
    id:forcastRoot
    anchors.fill: parent



    Row{
       anchors.centerIn: parent
        width: parent.width
        height: parent.height*.75
        spacing:forcastRoot.width *.01
        Repeater{

            model: 6
            delegate: Rectangle{
                color: "red"
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

