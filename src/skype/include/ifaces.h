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

#include "core/ibase.h"
#include "core/core_types.h"

namespace skype_sc {

struct IDBEvent
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0xb5413303) //skype_sc.IDBEvent
};

  
struct IDBWatcher
		: public Boss::Inherit<Boss::IBase>  {

	BOSS_DECLARE_IFACEID_HEX(0x27e199a6)  // CRC32(skype_sc.IDBWatcher)

	virtual Boss::RetCode BOSS_CALL AddObserver() = 0;
	virtual Boss::RetCode BOSS_CALL RemoveObserver() = 0;
};

struct IDBObserver
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0x7b2fc386)  // CRC32(skype_sc.IDBObserver)

    virtual Boss::RetCode BOSS_CALL ReactOnDbChanged(IDBEvent*) = 0;
};

} //namespace skype_sc

#endif  // !__MULTY_COMPONENT_IFACES_H__
