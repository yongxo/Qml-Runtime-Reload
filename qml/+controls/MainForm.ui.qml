import QtQuick 2.4

Rectangle {
    property alias mouseArea: mouseArea
anchors.fill: parent

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Text {
        anchors.centerIn: parent
        text: "Hello World"
    }
}
