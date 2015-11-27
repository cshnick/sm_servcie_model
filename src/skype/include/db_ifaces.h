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
#include "common/ienum.h"

namespace skype_sc {
using namespace Boss;

struct IConversation;
struct IUser;
struct IMessage
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IMessage) //

    virtual RetCode BOSS_CALL Author(IString **) = 0;
	virtual RetCode BOSS_CALL SetAuthor(IString *) = 0;
	virtual RetCode BOSS_CALL Body(IString **) = 0;
	virtual RetCode BOSS_CALL SetBody(IString *) = 0;
	virtual RetCode BOSS_CALL Timestamp(int *p_id) = 0;
	virtual RetCode BOSS_CALL SetTimestamp(int p_id) = 0;
	virtual RetCode BOSS_CALL SkypeTimestamp(int *p_id) = 0;
	virtual RetCode BOSS_CALL SetSkypeTimestamp(int p_id) = 0;
	virtual RetCode BOSS_CALL Id(int *p_id) = 0;
	virtual RetCode BOSS_CALL SetId(int p_id) = 0;
	virtual RetCode BOSS_CALL SkypeId(int *p_id) = 0;
	virtual RetCode BOSS_CALL SetSkypeId(int p_id) = 0;
	virtual RetCode BOSS_CALL SetConversation(IConversation *p_conv) = 0;
	virtual RetCode BOSS_CALL Conversation(IConversation **p_conv) = 0;
};

struct IConversation
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IConversation) //

	virtual RetCode BOSS_CALL SetName(IString *p_name) = 0;
	virtual RetCode BOSS_CALL Name(IString **p_name) = 0;
	virtual RetCode BOSS_CALL SetUsers(IEnum *p_users) = 0;
	virtual RetCode BOSS_CALL Users(IEnum **p_users) = 0;
};

struct IUser
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID(skype_sc.IUser) //

	virtual RetCode BOSS_CALL SetName(IString *p_name) = 0;
	virtual RetCode BOSS_CALL Name(IString **p_name) = 0;
	virtual RetCode BOSS_CALL SetSkypeName(IString *p_name) = 0;
	virtual RetCode BOSS_CALL SkypeName(IString **p_name) = 0;
};

} //namespace skype_sc



#endif /* SRC_SKYPE_INCLUDE_DB_IFACES_H_ */
