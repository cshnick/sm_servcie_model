/*
 * DBEventImpl.h
 *
 *  Created on: 06 окт. 2015 г.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_SERVICES_CORE_DBEVENTIMPL_H_
#define SRC_SKYPE_SERVICES_CORE_DBEVENTIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"

namespace skype_sc {

class DBEventImpl
 :public Boss::CoClass<skype_sc::service::id::DBEvent, IDBEvent> {

public:
	DBEventImpl();
	virtual ~DBEventImpl();
};

} //namespace skype_sc

#endif /* SRC_SKYPE_SERVICES_CORE_DBEVENTIMPL_H_ */
