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
    auto conversation = m_hlpr.Conversation();
    uint yesterday = QDateTime::currentDateTime().addDays(-1).toTime_t();
    if (m_hlpr.Timestamp() > yesterday) {
        if (!m_today.count(conversation.Id())) {
            m_today.emplace(conversation.Id());
        }
    }

    auto users = conversation.Users();
    std::for_each(users.begin(), users.end(), [this](const User_hlpr &usr) {
        if (!m_users.count(usr.SkypeName())) {
            m_users.emplace(usr.SkypeName());
            QStandardItem *item = new SkyContactsItem(QString::fromStdString(usr.Name()), "profile");
            item->setData(QString::fromStdString(usr.SkypeName()), SkypeNameRole);
            m_contacts->appendRow(item);
        }
    });
}

