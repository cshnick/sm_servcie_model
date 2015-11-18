/*
 * PlatformUtils.cpp
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#include "PlatformUtilsImpl.h"
#include <iostream>
#include "core/error_codes.h"

namespace skype_sc {
using namespace std;

PlatformUtilsImpl::PlatformUtilsImpl() {
	// TODO Auto-generated constructor stub
}

PlatformUtilsImpl::~PlatformUtilsImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::SkypeLocation(Boss::IString **) {
	cout << "PlatformUtils::SkypeLocation" << endl;
	return Boss::Status::NotImplemented;
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::UserSettingsDir(Boss::IString **)  {
	cout << "PlatformUtils::UserSettingsDir" << endl;
	return Boss::Status::NotImplemented;
}

} /* namespace skype_sc */
