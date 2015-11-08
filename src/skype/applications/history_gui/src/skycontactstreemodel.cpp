#include "skycontactstreemodel.h"

SkyContactsTreeModel::SkyContactsTreeModel(QObject *parent)
    :QStandardItemModel(parent)
{
    setColumnCount(1);
    QStandardItem *recent = new QStandardItem(QIcon(":/images/profile.svg"), "Recent");
    invisibleRootItem()->appendRow(recent);
    for (int i = 0; i < 10; i++) {
        QStandardItem *item = new QStandardItem(QString("row %1").arg(i));
        recent->appendRow(item);
    }
    QStandardItem *contacts = new QStandardItem(QIcon(":images/logoskype.svg"), "Contacts");
    invisibleRootItem()->appendRow(contacts);
}

