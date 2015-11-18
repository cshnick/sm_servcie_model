/*
 * SettingsImpl.h
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_SERVICES_SHCORE_SETTINGSIMPL_H_
#define SRC_SKYPE_SERVICES_SHCORE_SETTINGSIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"
#include "common/iistream.h"
#include "common/iostream.h"
#include "common/iserializable.h"
#include <memory>

namespace skype_sc {

class SettingsImplPrivate;
class SettingsImpl
		:public Boss::CoClass <skype_sc::service::id::Settings
		  	  , ISettings
			  , ISerializable > {
public:
	SettingsImpl();

	//ISerializable
	virtual RetCode BOSS_CALL Load(IIStream *stream) override;
	virtual RetCode BOSS_CALL Save(IOStream *stream) override;

	//ISettings
	virtual Boss::RetCode BOSS_CALL Accounts(Boss::IEnum **) override;

	virtual ~SettingsImpl();
private:
	friend class SettingsImplPrivate;
	std::unique_ptr<SettingsImplPrivate> p;
};

} /* namespace skype_sc */

#endif /* SRC_SKYPE_SERVICES_SHCORE_SETTINGSIMPL_H_ */
