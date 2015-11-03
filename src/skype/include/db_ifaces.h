/*
 * db_ifaces.h
 *
 *  Created on: 03 но€б. 2015 г.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_INCLUDE_DB_IFACES_H_
#define SRC_SKYPE_INCLUDE_DB_IFACES_H_

#include "core/ibase.h"
#include "core/core_types.h"
#include "common/istring.h"

namespace skype_sc {
struct IMessage
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IChat) //

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
