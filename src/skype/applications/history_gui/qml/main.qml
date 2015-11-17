import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQml.Models 2.2

ApplicationWindow {
    id: container_window
    title: qsTr("Sky history")
    width: 1366
    height: 768
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    ObjectModel {
        id: itemModel

        Rectangle {
            id: main_settings
            width: view.width / 2; height: view.height
            color: "lightblue"
            Text { text: "Settings"; font.bold: true; renderType: Text.NativeRendering; font.pointSize: 12
                   anchors {top: parent.top;horizontalCenter: parent.horizontalCenter; topMargin: 10 }
            }
        }
        MainView {
            width: view.width; height: view.height
            anchors.fill: undefined
            color: "transparent"
        }
    }

    ListView {
        id: view
        anchors { fill: parent}
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 1500
        cacheBuffer: 200
        currentIndex: 1
    }
}
