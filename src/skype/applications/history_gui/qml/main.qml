import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

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
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    SplitView {
        id: top_split
        anchors.fill: parent
        orientation: Qt.Horizontal

        TreesArea {
            Layout.minimumWidth: 250
        }

        DataArea {
            id: dataArea
            Layout.fillWidth: true
        }
    }
}
