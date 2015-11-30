#ifndef SKYCONTACTSTREEMODEL_H
#define SKYCONTACTSTREEMODEL_H

#include <QStandardItemModel>
#include <QStandardItem>
#include "skype_helpers.h"
#include <unordered_map>



class SkyContactsItem : public QStandardItem {

public:
    SkyContactsItem(const QString &text, const QString &image);
};


class SkyContactsTreeModel : public QStandardItemModel
{
    Q_OBJECT
    typedef std::unordered_map<std::string, std::string> UsersHash;
public:
    SkyContactsTreeModel(QObject *parent = 0);

    Q_INVOKABLE QString icon_path(const QModelIndex &ind);
    Q_INVOKABLE void dosmth() {}

    void processMessage(const skype_sc::Message_hlpr &m_hlpr);

private:
//    skype_sc::User_hlpr me;

    UsersHash m_users;
    UsersHash m_today;
    UsersHash m_yesterday;
    UsersHash two_weeks;

    QStandardItem *m_contacts = nullptr;
};

#endif // SKYCONTACTSTREEMODEL_H
