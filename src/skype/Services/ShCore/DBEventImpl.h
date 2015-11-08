#ifndef SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_
#define SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"
#include "core/ref_obj_ptr.h"
#include "common/string.h"
#include "common/enum.h"

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
	virtual RetCode BOSS_CALL Users(IEnum **p_users) override {
		return users.QueryInterface(p_users);
	}
	virtual Boss::RetCode BOSS_CALL SetUsers(IEnum *p_users) override {
		users = p_users;
		return Status::Ok;
	}
private:
	ref_ptr<IEnum> users;
};
class DBMessage : public SimpleCoClass<IMessage> {
public:
	DBMessage() {
		body = Base<String>::Create("Naked body");
	}

	virtual RetCode BOSS_CALL Body(IString **in_body) override {
		return body.QueryInterface(in_body);
	}
	virtual Boss::RetCode BOSS_CALL SetBody(IString *out_body) override {
		body = out_body;
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
	virtual RetCode BOSS_CALL SetConversation(IConversation *p_conv) override {
		conversation = p_conv;
		return Status::Ok;
	}
	virtual RetCode BOSS_CALL Conversation(IConversation **p_conv) override {
		return conversation.QueryInterface(p_conv);
	}

private:
	int id = -1;
	ref_ptr<IString> body;
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
