#include "skycontactstreemodel.h"
#include <QtCore>

SkyContactsItem::SkyContactsItem(const QString &text, const QString &image)
    : QStandardItem(text) {
    setData(image, Qt::UserRole);
}

SkyContactsTreeModel::SkyContactsTreeModel(QObject *parent)
    :QStandardItemModel(parent)
{
    setColumnCount(1);
    QStandardItem *recent = new SkyContactsItem("Recent", "qrc:/images/profile.svg");
    invisibleRootItem()->appendRow(recent);
    recent->appendRow(new SkyContactsItem("Test", "qrc:/images/clock.svg"));
    QStandardItem *contacts = new SkyContactsItem("Contacts", "qrc:/images/logoskype.svg");
    invisibleRootItem()->appendRow(contacts);
}

QString SkyContactsTreeModel::icon_path(const QModelIndex &ind) {
    return ind.data(Qt::UserRole).toString();
}

