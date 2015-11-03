/*
 * db_ifaces.h
 *
 *  Created on: 03 ����. 2015 �.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_INCLUDE_DB_IFACES_H_
#define SRC_SKYPE_INCLUDE_DB_IFACES_H_

#include "core/ibase.h"
#include "core/core_types.h"
#include "common/istring.h"

namespace skype_sc {
using namespace Boss;

struct IMessage
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IMessage) //

	virtual Boss::RetCode BOSS_CALL Body(IString **) = 0;
	virtual Boss::RetCode BOSS_CALL SetBody(IString *) = 0;
};

struct IConversation
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IConversation) //

};

struct IUser
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IUser) //
};

} //namespace skype_sc



#endif /* SRC_SKYPE_INCLUDE_DB_IFACES_H_ */
