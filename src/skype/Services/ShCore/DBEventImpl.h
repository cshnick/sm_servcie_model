#ifndef SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_
#define SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"
#include "core/ref_obj_ptr.h"
#include "common/string.h"
#include "common/enum.h"

namespace HistoryDB {
class Messages;
} //namespace HistoryDB
namespace skype_sc {
using namespace Boss;

class DBUser : public SimpleCoClass<IUser> {
public:
	virtual RetCode BOSS_CALL Name(IString **p_name) override {
		return m_name.QueryInterface(p_name);
	}
	virtual Boss::RetCode BOSS_CALL SetName(IString *p_name) override {
		m_name = p_name;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SkypeName(IString **p_name) override {
		return m_skype_name.QueryInterface(p_name);
	}
	virtual Boss::RetCode BOSS_CALL SetSkypeName(IString *p_name) override {
		m_skype_name = p_name;
		return Status::Ok;
	}

private:
	ref_ptr<IString> m_name;
	ref_ptr<IString> m_skype_name;
};

class DBConversation : public SimpleCoClass<IConversation> {
public:
	virtual RetCode BOSS_CALL SkypeId(int *p_id) override {
		*p_id = m_skype_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetSkypeId(int p_id) override {
		m_skype_id = p_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Id(int *p_id) override {
		*p_id = m_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetId(int p_id) override {
		m_id = p_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetName(IString *p_name) override {
		m_name = p_name;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Name(IString **p_name) override {
		return m_name.QueryInterface(p_name);
	}
	virtual RetCode BOSS_CALL Users(IEnum **p_users) override {
		return users.QueryInterface(p_users);
	}
	virtual Boss::RetCode BOSS_CALL SetUsers(IEnum *p_users) override {
		users = p_users;
		return Status::Ok;
	}
private:
	int m_id = -1, m_skype_id = -1;
	ref_ptr<IEnum> users;
	ref_ptr<IString> m_name;
};
class DBMessage : public SimpleCoClass<IMessage> {
public:
	DBMessage() {
		m_author = Base<String>::Create("Naked body");
	}
	DBMessage(std::unique_ptr<HistoryDB::Messages> &&);

	virtual RetCode BOSS_CALL Author(IString **author) override {
		return m_author.QueryInterface(author);
	}
	virtual Boss::RetCode BOSS_CALL SetAuthor(IString *author) override {
		m_author = author;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Body(IString **in_body) override {
		return body.QueryInterface(in_body);
	}
	virtual Boss::RetCode BOSS_CALL SetBody(IString *out_body) override {
		body = out_body;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Timestamp(int *p_id) override {
		*p_id = timestamp;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetTimestamp(int p_id) override {
		timestamp = p_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SkypeTimestamp(int *p_id) override {
		*p_id = skype_timestamp;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetSkypeTimestamp(int p_id) override {
		skype_timestamp = p_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Id(int *p_id) override {
		*p_id = id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetId(int p_id) override {
		id = p_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SkypeId(int *p_id) override {
		*p_id = skype_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetSkypeId(int p_id) override {
		skype_id = p_id;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL SetConversation(IConversation *p_conv) override {
		conversation = p_conv;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Conversation(IConversation **p_conv) override {
		return conversation.QueryInterface(p_conv);
	}

private:
	int id = -1, skype_id = -1, timestamp = -1, skype_timestamp = -1;

	ref_ptr<IString> body;
	ref_ptr<IString> m_author;
	ref_ptr<IConversation> conversation;
};

class DBEventImpl
		:public CoClass<skype_sc::service::id::DBEvent, IDBEvent> {


public:
	DBEventImpl();
	virtual ~DBEventImpl();

	virtual Boss::RetCode BOSS_CALL Message(IMessage **) override;
	virtual RetCode BOSS_CALL SetMessage(IMessage *mes) override {
		m_message = mes;
		return Status::Ok;
	}

private:
	ref_ptr<IMessage> m_message;
};

} //namespace skype_sc

#endif /* SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_ */
