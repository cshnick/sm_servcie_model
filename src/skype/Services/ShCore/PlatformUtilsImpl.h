/*
 * PlatformUtils.h
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_SERVICES_PLATFORMUTILS_PLATFORMUTILS_H_
#define SRC_SKYPE_SERVICES_PLATFORMUTILS_PLATFORMUTILS_H_

#include "iplatformutils.h"
#include "class_ids.h"
#include "core/co_class.h"
#include "common/istring.h"

namespace skype_sc {

class PlatformUtilsImpl
	:public Boss::CoClass  <skype_sc::service::id::PlatformUtils
	  	  , IPlatformUtils > {
public:
	PlatformUtilsImpl();
	virtual ~PlatformUtilsImpl();

	virtual Boss::RetCode BOSS_CALL SkypeLocation(Boss::IString **) override;
	virtual Boss::RetCode BOSS_CALL UserSettingsDir(Boss::IString **) override;
	virtual Boss::RetCode BOSS_CALL Exists(Boss::IString*, bool *) override;
};

} /* namespace skype_sc */

#endif /* SRC_SKYPE_SERVICES_PLATFORMUTILS_PLATFORMUTILS_H_ */
