//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     03.05.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#ifndef __MULTY_COMPONENT_IFACES_H__
#define __MULTY_COMPONENT_IFACES_H__

#include "db_ifaces.h"

#include "core/ibase.h"
#include "core/core_types.h"
#include "common/istring.h"
#include "common/ienum.h"
#include "common/callback.h"

namespace skype_sc {

struct IAccount
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0x665d6e11) //skype_sc.IAccount

	virtual Boss::RetCode BOSS_CALL Name(Boss::IString **) = 0;
	virtual Boss::RetCode BOSS_CALL FilePath(Boss::IString **) = 0;
	virtual Boss::RetCode BOSS_CALL HistoryDBPath(Boss::IString **) = 0;

	constexpr static const char* TDefaultAccount = "DefaultAccount";
	constexpr static const char* TAccounts = "Accounts";
	constexpr static const char* TName = "Name";
	constexpr static const char* TFilePath = "FilePath";
	constexpr static const char* THistoryDBPath = "HistoryDBPath";
};

struct ISettings
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0x600999e0) //skype_sc.ISettings

	virtual Boss::RetCode BOSS_CALL Accounts(Boss::IEnum **) = 0;
	virtual Boss::RetCode BOSS_CALL DefaultAccount(int *) = 0;
	virtual Boss::RetCode BOSS_CALL AsJsonString(IString **) = 0;
	virtual Boss::RetCode BOSS_CALL Update() = 0;
	virtual Boss::RetCode BOSS_CALL UpdateFromJson(IString *json_string) = 0;
};

struct IMessageCallback  {
	virtual ~IMessageCallback() {}
	virtual void Process(IMessage *) = 0;
};

struct IDBController
		: public Boss::Inherit<Boss::IBase> {

//	BOSS_DECLARE_IFACEID(skype_sc.DBController) //0x52dd9648
    BOSS_DECLARE_IFACEID_HEX(0x52dd9648)

	virtual Boss::RetCode BOSS_CALL Import() = 0;
    virtual Boss::RetCode BOSS_CALL Recent(Boss::IEnum **) = 0;
    virtual Boss::RetCode BOSS_CALL GetMessagesAsync(IMessageCallback *) = 0;
    virtual Boss::RetCode BOSS_CALL SetDBPath(Boss::IString *) = 0;
};

struct IDBEvent
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0xb5413303) //skype_sc.IDBEvent

	virtual Boss::RetCode BOSS_CALL Message(IMessage **) = 0;
	virtual RetCode BOSS_CALL SetMessage(IMessage *mes) = 0;
};

struct IDBObserver;
struct IDBWatcher
		: public Boss::Inherit<Boss::IBase>  {

	BOSS_DECLARE_IFACEID_HEX(0x27e199a6)  // CRC32(skype_sc.IDBWatcher)

	virtual Boss::RetCode BOSS_CALL AddObserver(IDBObserver *) = 0;
	virtual Boss::RetCode BOSS_CALL RemoveObserver(IDBObserver *) = 0;
	virtual Boss::RetCode BOSS_CALL SetWatchFile(Boss::IString *) = 0;
	virtual Boss::RetCode BOSS_CALL GetWatchFile(Boss::IString **) = 0;
};

struct IDBObserver
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0x7b2fc386)  // CRC32(skype_sc.IDBObserver)

    virtual Boss::RetCode BOSS_CALL ReactOnDbChanged(IDBEvent*) = 0;
};

struct IService
	: public Boss::Inherit<Boss::IBase> {

	//BOSS_DECLARE_IFACEID(skype_sc.IService) //0xc8946780
    BOSS_DECLARE_IFACEID_HEX(0xc8946780)

	virtual Boss::RetCode BOSS_CALL Start() = 0;
	virtual Boss::RetCode BOSS_CALL Stop() = 0;
    virtual Boss::RetCode BOSS_CALL Restart(Boss::IString *, Boss::IString *) = 0;
};

} //namespace skype_sc

#endif  // !__MULTY_COMPONENT_IFACES_H__
