#ifndef SKYCONTACTSTREEMODEL_H
#define SKYCONTACTSTREEMODEL_H

#include <QStandardItemModel>
#include <QStandardItem>
#include "skype_helpers.h"
#include <unordered_set>

class SkyContactsItem : public QStandardItem {

public:
    SkyContactsItem(const QString &text, const QString &image);
};

class SkyContactsTreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    typedef std::unordered_set<std::string> UserSet;
    typedef std::unordered_set<uint> ConversationSet;

    enum ExRole {
        NameRole = Qt::UserRole + 10,
        SkypeNameRole,
        TimestampRole,
		ConversationIdRole
    };

    SkyContactsTreeModel(QObject *parent = 0);

    Q_INVOKABLE QString icon_path(const QModelIndex &ind);
    Q_INVOKABLE void dosmth() {}

    void processMessage(const skype_sc::Message_hlpr &m_hlpr);

//    skype_sc::User_hlpr me;
private:

    UserSet m_users;
    ConversationSet m_set_today;
    ConversationSet m_set_yesterday;
    ConversationSet m_set_two_weeks;
    ConversationSet m_set_month;
    ConversationSet m_set_year;
    ConversationSet m_set_yplus;
    ConversationSet m_set_common;

    QStandardItem *m_item_recent = nullptr;
    QStandardItem *m_item_contacts = nullptr;
    QStandardItem *m_item_today = nullptr;
    QStandardItem *m_item_yesterday = nullptr;
    QStandardItem *m_item_two_weeks = nullptr;
    QStandardItem *m_item_month = nullptr;
    QStandardItem *m_item_year = nullptr;
    QStandardItem *m_item_yplus = nullptr;
};

#endif // SKYCONTACTSTREEMODEL_H
