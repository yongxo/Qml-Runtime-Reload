import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id:wdw
    visible:true
    height: 720
    width: 1280

    Connections{
        target: app
        onStarted:{
            close();
        }
    }

    Component.onCompleted: console.log("Application Window")

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem { text: "Open..." }
            MenuItem { text: "Close" }
            MenuItem { text: "Reload"; onTriggered: { app.reload() ; }}
            MenuItem { text: "Non Window"; onTriggered: { app.usingWindow = false } }
        }

        Menu {
            title: "Edits"
            MenuItem { text: "Cut" }
            MenuItem { text: "Copy" }
            MenuItem { text: "Paste" }
        }
        Menu {
            title: "Settings"
            MenuItem { text: "Location" }
        }
    }

    TabView{
        id:fakeLoader
        frameVisible: false
        tabsVisible: false
        anchors.fill: parent
           Tab{
                source: app.currentScreen
                anchors.fill: parent
                active: true
            }
    }



    statusBar: StatusBar{
        RowLayout {
                   anchors.fill: parent
                   Label { text: "No Weather Information" }
               }
    }
}

