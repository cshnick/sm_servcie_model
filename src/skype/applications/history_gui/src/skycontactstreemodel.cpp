#include "skycontactstreemodel.h"
#include <QtCore>

using namespace skype_sc;

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

    m_contacts = new SkyContactsItem("Contacts", "profile");
    invisibleRootItem()->appendRow(m_contacts);
}

QString SkyContactsTreeModel::icon_path(const QModelIndex &ind) {
    return ind.data(Qt::UserRole).toString();
}

void SkyContactsTreeModel::processMessage(const skype_sc::Message_hlpr &m_hlpr) {
    auto users = m_hlpr.Conversation().Users();
    std::for_each(users.begin(), users.end(), [this](const User_hlpr &usr) {
        if (!m_users.count(usr.Name())) {
            m_users.emplace(usr.Name(), usr);
            QStandardItem *item = new SkyContactsItem(QString::fromStdString(usr.Name()), "profile");
            m_contacts->appendRow(item);
        }
    });
}

