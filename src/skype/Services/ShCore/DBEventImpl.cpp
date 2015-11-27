#include "DBEventImpl.h"
#include <iostream>
#include "core/error_codes.h"
#include "history_main_db.hpp"
#include "common/string.h"

namespace skype_sc {
using namespace std;
using namespace litesql;
using namespace HistoryDB;
using namespace Boss;

DBEventImpl::DBEventImpl() {
	m_message = Base<DBMessage>::Create();
}

DBEventImpl::~DBEventImpl() {
	// TODO Auto-generated destructor stub
}

RetCode DBEventImpl::Message(IMessage **pp_mes) {
	return m_message.QueryInterface(pp_mes);
}

DBMessage::DBMessage(std::unique_ptr<HistoryDB::Messages> &&hm) {
	id = hm->id;
	skype_id = hm->skype_id;
	timestamp = hm->timestamp;
	body = Base<String>::Create(hm->body);
	m_author = Base<String>::Create(hm->author);

//	ref_ptr<IConversation> conversation;
}

} // namespace skype_sc
