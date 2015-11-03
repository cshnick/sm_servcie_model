#include "DBEventImpl.h"
#include <iostream>
#include "core/error_codes.h"

namespace skype_sc {

DBEventImpl::DBEventImpl() {
	m_message = Base<DBMessage>::Create();
}

DBEventImpl::~DBEventImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode DBEventImpl::Message(IMessage **pp_mes) {
	return m_message.QueryInterface(pp_mes);
}

} // namespace skype_sc
