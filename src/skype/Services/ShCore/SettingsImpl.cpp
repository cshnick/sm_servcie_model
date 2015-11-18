/*
 * SettingsImpl.cpp
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: ilia
 */

#include "SettingsImpl.h"

#include "core/error_codes.h"
#include "common/string_helper.h"

#include "common/ienum.h"
#include "common/enum.h"
#include "common/enum_helper.h"
#include "common/string.h"
#include "common/string_helper.h"

#include <dirent.h>
#include <iostream>

#include "PlatformUtilsImpl.h"

namespace skype_sc {
using namespace std;
using namespace Boss;

class AccountImpl
		: public SimpleCoClass<IAccount> {
public:
	AccountImpl(const std::string &name, const std::string &path, const std::string &hdb_path) {
		m_name = Base<String>::Create(name);
		m_path = Base<String>::Create(path);
		history_db_path = Base<String>::Create(hdb_path);
	}

	AccountImpl() = delete;

	virtual Boss::RetCode BOSS_CALL Name(Boss::IString **name) {return m_name.QueryInterface(name);}
	virtual Boss::RetCode BOSS_CALL FilePath(Boss::IString **path) {return m_path.QueryInterface(path);}
	virtual Boss::RetCode BOSS_CALL HistoryDBPath(Boss::IString **path) {return history_db_path.QueryInterface(path);}

private:
	ref_ptr<String> history_db_path;
	ref_ptr<String> m_path;
	ref_ptr<String> m_name;
};

class SettingsImplPrivate {
	friend class SettingsImpl;
public:
	SettingsImplPrivate(SettingsImpl *q) : q(q) {
		pu = Base<PlatformUtilsImpl>::Create();
	}
	Boss::RetCode Accounts(Boss::IEnum **res) {
		DIR *d;
		ref_ptr<IString> skype_location;
		pu->SkypeLocation(skype_location.GetPPtr());

		ref_ptr<Enum> res_enum = Base<Enum>::Create();
		struct dirent *dir, *subdir;
		const char *char_loc = StringHelper(skype_location).GetString<IString::AnsiString>().c_str();
		d = opendir(char_loc);
		if (d)	{
			while ((dir = readdir(d)) != NULL) {
				if (dir->d_type == DT_DIR) { //Directory
					if (!strcmp(dir->d_name, ".")) continue;
					if (!strcmp(dir->d_name, "..")) continue;
					DIR *subd;
					char buf[512];
					sprintf(buf, "%s/%s", char_loc, dir->d_name);
					subd = opendir(buf);
					while ((subdir = readdir(subd)) != NULL) {
						if (subdir->d_type == DT_REG && !strcmp(subdir->d_name, "main.db")) {
							res_enum->AddItem(Base<AccountImpl>::Create(dir->d_name, buf, ""));
						}
					}
				}
			}

			closedir(d);
		}

		return Boss::Status::Ok;
	}
private:
private:
	SettingsImpl *q;

	ref_ptr<IPlatformUtils> pu;
};

SettingsImpl::SettingsImpl() {
	p.reset(new SettingsImplPrivate(this));
	cout << "SettingsImpl::SettingsImpl()" << endl;
}

SettingsImpl::~SettingsImpl() {
	// TODO Auto-generated destructor stub
}

RetCode BOSS_CALL SettingsImpl::Load(IIStream *stream) {
	cout << "SettingsImpl::Load" << endl;
	return Boss::Status::Ok;
}
RetCode BOSS_CALL SettingsImpl::Save(IOStream *stream) {
	cout << "SettingsImpl::Save" << endl;
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL SettingsImpl::Accounts(Boss::IEnum **result) {
	cout << "SettingsImpl::Accounts" << endl;
	return p->Accounts(result);
}

} /* namespace skype_sc */
