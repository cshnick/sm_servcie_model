import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    TextField {
        id: search_field
        height: 30
        width: parent.width
        style: TextFieldStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 24
                border.color: "#333"
                border.width: 1
            }
        }

        onEditingFinished: {
            console.log("search_field editing finished")
            sky_list.filter(search_field.text)
        }
    }

    ProgressBar {
        id: progress_bar
        y: search_field.height
        height: 2
        width: parent.width
        value: sky_model.loadProgress
        minimumValue: 0
        maximumValue: 100

        Connections {
            target: sky_model
            onLoadFinished: {
                progress_bar.visible = false
            }
        }

        style: ProgressBarStyle {
            background: Rectangle {
                color: "white"
                implicitHeight: 2
            }
            progress: Rectangle {
                color: "#03A9F4"
            }
        }
    }

    SkyList {
        id: sky_list
        property int filter_after : 1
        function text_changed(text) {
            if (text.length > filter_after) {
                filter(text)
            }
        }

        anchors.fill: undefined
        x: 0
        y: search_field.height + 2
        clip: true
        height: parent.height - search_field.height -2
        width: parent.width

        Connections {
            target: search_field
            onTextChanged: {
                sky_list.text_changed(search_field.text)
            }
        }
    }

}

