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

        function createaAccSettingsRect(text, path) {
            var cmp = Qt.createComponent("AccSettingsRect.qml");
            var obj = cmp.createObject(settings_container, {
                                           "color": "transparent",
                                           "height": 50,
                                           "text": text,
                                           "path": path
                                       });
            if (obj == null) {
                console.log("Error creating object");
            }
        }

        Rectangle {
            id: main_settings
            width: view.width / 2; height: view.height
            color: "white"
            Text {
                id: header
                text: "Settings"; font.bold: true; renderType: Text.NativeRendering; font.pointSize: 12
                anchors {top: parent.top;horizontalCenter: parent.horizontalCenter; topMargin: 10 }
            }

            Column {

                id: settings_container
                spacing: 2
                anchors {top: header.bottom; bottom: parent.bottom; left: parent.left; right: parent.right; leftMargin: 2; rightMargin: 2}
                Text {
                    width: parent.width
                    text: "Accounts";
                    color: "black"
                    renderType: Text.NativeRendering
                    font.pointSize: 12
                    font.bold: true
                }
                Rectangle {
                    width: parent.width
                    height: 1
                    color: "black"
                }
            }

            Component.onCompleted: {
                var accs = sky_model.settings()["Accounts"]
                console.log(o)
                for(var acc in accs) {
                   console.log(k, o[k]);
                   itemModel.createaAccSettingsRect(k, o[k])
                }
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
