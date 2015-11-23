import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Rectangle {
    id: accSettingsTop

    property alias text: txt.text
    property alias path: path_field.text

    width: parent.width
    Column {
        spacing: 4
        anchors.fill: parent
        Text {
            id: txt
            width: parent.width
            font.bold: true
            renderType: Text.NativeRendering
            font.pointSize: 11
            color: "#333"
        }
        TextField {
            id: path_field
            width: parent.width

            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    color : "lightblue"
                    radius: 0
                    border.color: "#333"
                    border.width: 0
                }
            }
            Button {
                anchors {verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: 4}
                width: 30
                height: 20
                text: "..."
                onClicked: {
                    fileDialog.folder = "file://" + accSettingsTop.path
                    fileDialog.visible = true
                }
                style: ButtonStyle {
                    background: Rectangle {
                        border.width: control.hovered ? 1 : 0
                        border.color: "#555"
                        color: "lightblue"
                        radius: 0
                    }
                }
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: accSettingsTop.text
                selectFolder: true
                onAccepted: {
                    visible: false
                }
                onRejected: {
                    visible = false
                }
                Component.onCompleted: visible = false
            }
        }
    }
}


