#include "DBEventImpl.h"
#include <iostream>
#include "core/error_codes.h"

namespace skype_sc {

DBEventImpl::DBEventImpl() {
	// TODO Auto-generated constructor stub
}

DBEventImpl::~DBEventImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode DBEventImpl::Message(IMessage **) {
	std::cout << "DBEventImpl::Message" << std::endl;
	return Boss::Status::NotImplemented;
}

} // namespace skype_sc
