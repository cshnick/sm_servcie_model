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

//    skype_sc::User_hlpr me;
private:
    template<typename ...Args>
    void newIfNull(QStandardItem *chck_val, QStandardItem *parent, const Args &...args) {
    	if (!chck_val) {
    		m_today = new SkyContactsItem(args...);
    		parent->appendRow(chck_val);
    	}
    }


    UserSet m_users;
    ConversationSet today;
    ConversationSet yesterday;
    ConversationSet two_weeks;

    QStandardItem *m_recent = nullptr;
    QStandardItem *m_contacts = nullptr;
    QStandardItem *m_today = nullptr;
    QStandardItem *m_yesterday = nullptr;
    QStandardItem *m_two_weeks = nullptr;
};

#endif // SKYCONTACTSTREEMODEL_H
