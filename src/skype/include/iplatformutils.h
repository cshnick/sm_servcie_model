/*
 * iplatformutils.h
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_INCLUDE_IPLATFORMUTILS_H_
#define SRC_SKYPE_INCLUDE_IPLATFORMUTILS_H_

#include "core/ibase.h"
#include "core/core_types.h"
#include "common/istring.h"
#include "common/ienum.h"

namespace skype_sc {

struct IPlatformUtils
		: public Boss::Inherit<Boss::IBase> {

	BOSS_DECLARE_IFACEID_HEX(0xf7956c2d) //skype_sc.IPlatformUtils

	virtual Boss::RetCode BOSS_CALL SkypeLocation(Boss::IString **) = 0;
	virtual Boss::RetCode BOSS_CALL UserSettingsDir(Boss::IString **) = 0;
	virtual Boss::RetCode BOSS_CALL Exists(Boss::IString*, bool *) = 0;
};

} //namespace skype_sc

#endif /* SRC_SKYPE_INCLUDE_IPLATFORMUTILS_H_ */
