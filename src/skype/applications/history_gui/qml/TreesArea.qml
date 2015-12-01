import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root_tree_views
    property int icon_size: 24
    Layout.minimumWidth: 250

    TreeView {
        anchors.fill: parent

        TableViewColumn {
            title: "Name"
            role: "display"
            width: root_tree_views.width - 2
        }
        headerVisible: false

        itemDelegate: Rectangle {
            id: rect_delegate
            //color: "lightblue"
            RowLayout {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - 4
                height: parent.height
                spacing: 4
                Image {
                    id: icon
                    Layout.preferredWidth: root_tree_views.icon_size
                    Layout.preferredHeight: root_tree_views.icon_size
                    width: root_tree_views.icon_size
                    height: root_tree_views.icon_size
                    source: sky_contacts_model.icon_path(styleData.index)
                    smooth:  true
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: root_tree_views.icon_size
                    color: styleData.selected ? "lightblue" : "transparent"
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        x: 2
                        renderType: Text.NativeRendering
                        text: styleData.value
                    }
                }
            }
        }

        rowDelegate: Rectangle {
            width: root_tree_views.icon_size + 4
            height: root_tree_views.icon_size + 4
        }

        onCurrentIndexChanged: {
            console.log("Current index changed to " + currentIndex)
            //console.log("Current index data: " + sky_contacts_model.icon_path(currentIndex))
            //sky_contacts_model.icon_path(currentIndex)

        }
        onActivated: {
            console.log("Activated index: " + index.data)
            sky_model.contactTreeItemSelected(index)
        }

        style : TreeViewStyle {
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

            branchDelegate: Image {
                x: -5
                source: styleData.isExpanded ? "qrc:/images/expanded.png" : "qrc:/images/haschildren.png"
                width: 9
                height: 9
            }

            incrementControl: inc_dec_control
            decrementControl: inc_dec_control

            scrollBarBackground: Item {
                implicitWidth: 6
                implicitHeight: 26
            }
            activateItemOnSingleClick: true
            indentation: 18
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        model: sky_contacts_model
    }
}
