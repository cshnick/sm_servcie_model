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
    typedef std::unordered_set<std::string> UserSet;
    typedef std::unordered_set<int> ConversationSet;

public:
    enum ExRole {
        NameRole = Qt::UserRole + 10,
        SkypeNameRole,
        TimestampRole,
    };

    SkyContactsTreeModel(QObject *parent = 0);

    Q_INVOKABLE QString icon_path(const QModelIndex &ind);
    Q_INVOKABLE void dosmth() {}

    void processMessage(const skype_sc::Message_hlpr &m_hlpr);

private:
//    skype_sc::User_hlpr me;

    UserSet m_users;
    ConversationSet m_today;
    ConversationSet m_yesterday;
    ConversationSet two_weeks;

    QStandardItem *m_contacts = nullptr;
};

#endif // SKYCONTACTSTREEMODEL_H
