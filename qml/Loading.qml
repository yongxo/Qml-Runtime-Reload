import QtQuick 2.4


Item {

    id:loadingWindow
    visible: true
    width:1280
    height:720


    Text{
        anchors.centerIn: parent
        font.pointSize: 32
        text:"Loading"
        color:"white"
    }
}
