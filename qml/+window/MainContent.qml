

import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

ApplicationWindow {
    id:wdw
  visible:true
  height: 720
  width: 1280

  Component.onCompleted: console.log("Application Window")

  menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem { text: "Open..." }
            MenuItem { text: "Close" }
             MenuItem { text: "Reload"; onTriggered: { app.reload() ;wdw.close() }}
              MenuItem { text: "Switch"; onTriggered: { app.reload() } }
        }

        Menu {
            title: "Edit"
            MenuItem { text: "Cut" }
            MenuItem { text: "Copy" }
            MenuItem { text: "Paste" }
        }
    }
}
