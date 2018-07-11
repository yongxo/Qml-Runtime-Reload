import QtQuick 2.4
import QtQuick.Controls 1.2

Item{
    id:simpleBtn
    width: menuColumn.width *.45
    height: menuColumn.height*.10
    property color color:"green"
    property string label:qsTr("lorem")
    signal clicked()
    Rectangle{
        radius: 5
        anchors.fill: parent
        color: parent.color
        opacity: ms.pressed ? .25 : .75
        Behavior on opacity {
            PropertyAnimation{ duration: 100}
        }
    }
    Text {
        id: label
        text: parent.label
        anchors.centerIn: parent
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
    }
    MouseArea{
        id:ms
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
