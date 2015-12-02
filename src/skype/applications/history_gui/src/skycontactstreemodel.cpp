#include "skycontactstreemodel.h"
#include <QtCore>

using namespace skype_sc;

SkyContactsItem::SkyContactsItem(const QString &text, const QString &image) :
		QStandardItem(text) {
	setData(QString("qrc:/images/%1.png").arg(image), Qt::UserRole);
}

SkyContactsTreeModel::SkyContactsTreeModel(QObject *parent) :
		QStandardItemModel(parent) {
	setColumnCount(1);
	m_recent = new SkyContactsItem("Recent", "clock");
	invisibleRootItem()->appendRow(m_recent);
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
        if (!today.count(conversation.SkypeId())) {
            today.emplace(conversation.SkypeId());
            if (!m_today) {
            	m_today = new SkyContactsItem("Today", "clock");
            	m_recent->appendRow(m_today);
            }
            QString qstring_name = QString::fromStdString(conversation.Name());
            m_today->appendRow(new SkyContactsItem(qstring_name, "chat"));
        }
    }
	auto users = conversation.Users();
	std::for_each(users.begin(), users.end(),[this](const User_hlpr &usr) {
		if (!m_users.count(usr.SkypeName())) {
			m_users.emplace(usr.SkypeName());
			QStandardItem *item = new SkyContactsItem(QString::fromStdString(usr.Name()), "profile");
			item->setData(QString::fromStdString(usr.SkypeName()), SkypeNameRole);
			m_contacts->appendRow(item);
		}
	});
}

