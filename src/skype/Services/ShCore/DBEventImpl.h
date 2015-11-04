#ifndef SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_
#define SRC_SKYPE_SERVICES_SHCORE_DBEVENTIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"
#include "core/ref_obj_ptr.h"
#include "common/string.h"

namespace skype_sc {
using namespace Boss;
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

private:
	int id = -1;
	ref_ptr<IString> body;
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
