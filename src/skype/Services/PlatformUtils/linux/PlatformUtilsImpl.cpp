/*
 * PlatformUtils.cpp
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#include "../PlatformUtilsImpl.h"
#include <iostream>
#include "core/error_codes.h"
#include "common/string.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace skype_sc {
using namespace std;
using namespace Boss;

PlatformUtilsImpl::PlatformUtilsImpl() {
	// TODO Auto-generated constructor stub
	cout << "PlatformUtils::PlatformUtils()" <<  endl;
}

PlatformUtilsImpl::~PlatformUtilsImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode BOSS_CALL PlatformUtilsImpl::SkypeLocation(Boss::IString **res) {
	struct passwd *pw = getpwuid(getuid());
	std::string std_loc(pw->pw_dir);
	std_loc.append("/.Skype/");

	auto location = Base<String>::Create(std_loc);
	return location.QueryInterface(res);
}
Boss::RetCode BOSS_CALL PlatformUtilsImpl::UserSettingsDir(Boss::IString **)  {
	cout << "PlatformUtils::UserSettingsDir" << endl;
	return Boss::Status::NotImplemented;
}

} /* namespace skype_sc */
