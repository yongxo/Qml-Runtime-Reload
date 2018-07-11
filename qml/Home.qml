
import QtQuick 2.4
import QtQuick.Controls 1.2

Item {
    id:homeScreen
    anchors.fill: parent

    Rectangle{
        anchors.fill: parent
        color:"darkgrey"
    }

    Item{
        id:menuContainer
        anchors.fill: parent

        Rectangle{
            anchors.fill: parent
            color:"darkgrey"
        }

        Column{
            id:menuColumn
            spacing: parent.height *.02
            width: homeScreen.width *.15
            anchors{
                top:parent.top
                left:parent.left
                bottom:parent.bottom
            }

            Text{
                text:qsTr("Simple Menu")
            }

            SimpleButton {
                id: simpleBtn
                label: qsTr("Reload QML")
                onClicked: app.reload()
            }
            SimpleButton{
                label:qsTr("Change Skin")
                onClicked: app.currentSkinEntry = "controls"
            }
            SimpleButton{
                label:qsTr("Use QQuickWindow")
                onClicked: app.usingWindow = true
            }
        }

        Item{
            id:displayBox
            Component.onCompleted: state="open"
            anchors{
                top:parent.top
                right: parent.right
                left: parent.right
                bottom:parent.bottom
            }
            Rectangle{
                anchors.fill: parent
                color:"lightgrey"
            }

            Text{
                anchors.centerIn: parent
                width: parent.width* .45
                height: parent.height
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                text:"Qml Runtime Reload. This part of the example is utilizing a QQuickView to display QML elements.
            If you would like to see what ApplicationWindow looks like, choose 'Use QQuickWindow' Otherwise, choose 'Change Skin' to see how changing a theme looks

            Or, you can change some of the QML source and then click 'Reload' to see it in action.

Thanks for attending!!"
            }

            states: [
                State {
                    name: "closed"
                  AnchorChanges{
                      target: displayBox
                      anchors.left: menuContainer.right
                  }
                },
                State {
                    name: "open"
                    AnchorChanges{
                        target: displayBox
                        anchors.left: menuContainer.horizontalCenter
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    AnchorAnimation{
                        duration: 500
                        easing.type: Easing.InCubic
                    }
                }
            ]
        }

    }
}

