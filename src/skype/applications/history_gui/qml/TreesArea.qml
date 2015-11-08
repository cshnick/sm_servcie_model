import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Item {
    id: root_tree_views
    Layout.minimumWidth: 250

    TreeView {
        anchors.fill: parent
        TableViewColumn {
            title: "Name"
            role: "display"
            width: root_tree_views.width - 2
        }

        model: sky_contacts_model
    }
}
