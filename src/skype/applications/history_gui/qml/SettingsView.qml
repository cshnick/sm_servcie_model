import QtQuick 2.0

Rectangle {
    id: settings_view_container

    Text {
        id: header
        text: "Settings"; font.bold: true; renderType: Text.NativeRendering; font.pointSize: 12
        anchors {top: parent.top;horizontalCenter: parent.horizontalCenter; topMargin: 10 }
    }
    ListModel { id: accounts_model }
    Column {
        id: settings_container
        spacing: 4
        anchors {top: header.bottom; bottom: parent.bottom; left: parent.left; right: parent.right; leftMargin: 2; rightMargin: 2}

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
        }

        ListView {
            id: accounts_view

            spacing: 4
            height: parent.height / 2
            width: parent.width
            delegate: AccSettingsRect {
                text: AccName
                path: HistoryDBPath
                height: 50
            }
            model: accounts_model
            highlight: Rectangle {
                y: accounts_view.currentItem.y
                color: "#ddd"
                border.width: 1
                border.color: "#ddd"
            }
            highlightMoveVelocity: 4500
            highlightFollowsCurrentItem: true
        }

        Component.onCompleted: {
            var accs = g_settings["Accounts"]
            for(var i in accs) {
                //settings_view_container.createaAccSettingsRect(accs[i].Name, accs[i].HistoryDBPath)
                accounts_model.append({AccName: accs[i].Name, HistoryDBPath : accs[i].HistoryDBPath})
            }
            accounts_view.currentIndex = 0
        }
    }
}
