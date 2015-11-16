#include "skycontactstreemodel.h"
#include <QtCore>

SkyContactsItem::SkyContactsItem(const QString &text, const QString &image)
    : QStandardItem(text) {
    setData(QString("qrc:/images/%1.png").arg(image), Qt::UserRole);
}

SkyContactsTreeModel::SkyContactsTreeModel(QObject *parent)
    :QStandardItemModel(parent)
{
    setColumnCount(1);
    QStandardItem *recent = new SkyContactsItem("Recent", "clock");
    invisibleRootItem()->appendRow(recent);
    QStandardItem *today = new SkyContactsItem("Today", "clock");
    QStandardItem *yesterday = new SkyContactsItem("Yesterday", "clock");
    recent->appendRow(today);
        today->appendRow(new SkyContactsItem("User 3", "profile"));
        today->appendRow(new SkyContactsItem("User 7", "profile"));
    recent->appendRow(yesterday);
        yesterday->appendRow(new SkyContactsItem("User 4", "profile"));
        yesterday->appendRow(new SkyContactsItem("User 6", "profile"));
        yesterday->appendRow(new SkyContactsItem("User 3", "profile"));

    QStandardItem *contacts = new SkyContactsItem("Contacts", "profile");
    invisibleRootItem()->appendRow(contacts);
    for (int i = 0; i < 10; i++) {
        contacts->appendRow(new SkyContactsItem(QString("User %1").arg(i), "profile"));
    }
}

QString SkyContactsTreeModel::icon_path(const QModelIndex &ind) {
    return ind.data(Qt::UserRole).toString();
}

