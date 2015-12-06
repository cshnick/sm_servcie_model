#include "skycontactstreemodel.h"
#include <QtCore>

using namespace skype_sc;
using namespace std;

SkyContactsItem::SkyContactsItem(const QString &text, const QString &image) :
		QStandardItem(text) {
	setData(QString("qrc:/images/%1.png").arg(image), Qt::UserRole);
}

SkyContactsTreeModel::SkyContactsTreeModel(QObject *parent) :
		QStandardItemModel(parent) {
	setColumnCount(1);
	m_item_recent = new SkyContactsItem("Recent", "clock");
	invisibleRootItem()->appendRow(m_item_recent);
	m_item_contacts = new SkyContactsItem("Contacts", "profile");
	invisibleRootItem()->appendRow(m_item_contacts);
}

QString SkyContactsTreeModel::icon_path(const QModelIndex &ind) {
	return ind.data(Qt::UserRole).toString();
}

namespace { //Anonimous
struct ChatAdder {
	void appendCond() {
		bool lcond = lb_time == 0 ? true : timestamp > lb_time;
		bool ucond = ub_time == 0 ? true : timestamp > ub_time;

		if (lcond && ucond) {
			int skypeId = ch->SkypeId();
			if (!cache->count(skypeId)) {
				cache->emplace(skypeId);
				if (!*parentItem) {
					*parentItem = new SkyContactsItem(title, "clock");
					(*parentParentItem)->appendRow(*parentItem);
				}
				QString qstring_name = QString::fromStdString(ch->Name());
                QStandardItem *chat = new SkyContactsItem(qstring_name, "chat");
                chat->setData(skypeId, SkyContactsTreeModel::ConversationIdRole);
                (*parentItem)->appendRow(chat);

			}
		}
	}
	Conversation_hlpr *ch;
	int timestamp, lb_time, ub_time;
	SkyContactsTreeModel::ConversationSet *cache;
	QStandardItem **parentItem, **parentParentItem;
	QString title;
};
} //namespace Anonimous

void SkyContactsTreeModel::processMessage(const skype_sc::Message_hlpr &m_hlpr) {
	auto conversation = m_hlpr.Conversation();

	int hlpr_ts = m_hlpr.SkypeTimestamp();

	int today_00_00     = QDateTime(QDate::currentDate(), QTime(0, 0)).toTime_t();
	int yesterday_00_00 = QDateTime(QDate::currentDate().addDays(-1), QTime(0, 0)).toTime_t();
	int two_weeks_00_00 = QDateTime(QDate::currentDate().addDays(-14), QTime(0, 0)).toTime_t();
	int month_ago_00_00 = QDateTime(QDate::currentDate().addMonths(-1), QTime(0, 0)).toTime_t();
	int year_ago_00_00  = QDateTime(QDate::currentDate().addYears(-1), QTime(0, 0)).toTime_t();

	ChatAdder{&conversation, hlpr_ts, today_00_00    , 0              , &m_set_common, &m_item_today    , &m_item_recent, "Today"}.appendCond();
	ChatAdder{&conversation, hlpr_ts, yesterday_00_00, today_00_00    , &m_set_common, &m_item_yesterday, &m_item_recent, "Yesterday"}.appendCond();
	ChatAdder{&conversation, hlpr_ts, two_weeks_00_00, yesterday_00_00, &m_set_common, &m_item_two_weeks, &m_item_recent, "Two weeks"}.appendCond();
	ChatAdder{&conversation, hlpr_ts, month_ago_00_00, two_weeks_00_00, &m_set_common, &m_item_month    , &m_item_recent, "Latest month"}.appendCond();
	ChatAdder{&conversation, hlpr_ts, year_ago_00_00 , month_ago_00_00, &m_set_common, &m_item_year     , &m_item_recent, "Latest year"}.appendCond();
	ChatAdder{&conversation, hlpr_ts, 0              , year_ago_00_00 , &m_set_common, &m_item_yplus    , &m_item_recent, "More than year"}.appendCond();

	auto users = conversation.Users();
	std::for_each(users.begin(), users.end(),[this](const User_hlpr &usr) {
		if (!m_users.count(usr.SkypeName())) {
			m_users.emplace(usr.SkypeName());
			QStandardItem *item = new SkyContactsItem(QString::fromStdString(usr.Name()), "profile");
			item->setData(QString::fromStdString(usr.SkypeName()), SkypeNameRole);
			m_item_contacts->appendRow(item);
		}
	});
}

