import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle {
    anchors.fill: parent

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

