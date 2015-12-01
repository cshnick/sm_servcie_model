import QtQuick 2.0
import QtQuick.Controls.Styles 1.2

ScrollViewStyle {
    handle: Item {
        implicitWidth: 14
        implicitHeight: 26
        Rectangle {
            color: "#03A9F4"
            anchors.fill: parent
            anchors.topMargin: 0
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
        }
    }
    Component {
        id: inc_dec_control
        Item {
            visible: false
        }
    }

    incrementControl: inc_dec_control
    decrementControl: inc_dec_control

    scrollBarBackground: Item {
        implicitWidth: 6
        implicitHeight: 26
    }
}
