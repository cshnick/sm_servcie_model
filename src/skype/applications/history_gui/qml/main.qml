import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQml.Models 2.2

import "Helper.js" as DynObj

ApplicationWindow {
    id: container_window
    title: qsTr("Sky history")
    width: 1366
    height: 768
    visible: true

    property var g_settings : sky_model.settings()
    function updateSettings(new_settings) {
        sky_model.updateSettings(new_settings)
    }

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("&File")
//            MenuItem {
//                text: qsTr("E&xit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

    ObjectModel {
        id: itemModel

        SettingsView {
            id: main_settings
            width: view.width / 2; height: view.height
            color: "#eee"
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
