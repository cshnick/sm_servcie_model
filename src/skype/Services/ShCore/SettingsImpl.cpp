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
#include "common/file_stream.h"
#include "core/exceptions.h"
#include "common/buffer.h"

#include <dirent.h>
#include <iostream>

#include <json/json.h>

#include <skype_helpers.h>

#include "PlatformUtilsImpl.h"

namespace skype_sc {
using namespace std;
using namespace Boss;

BOSS_DECLARE_RUNTIME_EXCEPTION(Settings)

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
	static const char* json_filename;

	SettingsImplPrivate(SettingsImpl *q)
		: q(q), pu_h(Base<PlatformUtilsImpl>::Create()) {
		if (!loadAccounts()) {
			AccountsDefault(m_accounts.GetPPtr());
		}
	}
	bool loadAccounts() {
		auto str = Base<String>::Create(json_filename);
		if (!pu_h.Exists(json_filename)) return false;

		auto fs = Base<IFileStream>::Create(json_filename);
		ref_ptr<IBuffer> buf;
		fs->Read(buf.GetPPtr());
		UInt sz;
		if (buf->GetSize(&sz) != Status::Ok) {
			throw SettingsException("Invalid buffer size");
		}
		const void* data = 0;
		if (buf->GetData(&data) != Status::Ok) {
			throw SettingsException("Invalid buffer data");
		}

		std::string c_data = (const char*)data;

		json_tokener *tok = json_tokener_new();
		json_object *jobj = 0;
		enum json_tokener_error jerr;
		do {
			jobj = json_tokener_parse_ex(tok, c_data.c_str(), c_data.size());
		} while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue);

		if (jerr != json_tokener_success) {
			throw SettingsException(json_tokener_error_desc(jerr));
		}

		json_parse(jobj);

		return false;
	}
	void json_parse(json_object * jobj) {
		enum json_type type;
		json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
			type = json_object_get_type(val);
			switch (type) {
			case json_type_boolean:
			case json_type_double:
			case json_type_int:
			case json_type_string:
				break;
			case json_type_object: printf("json_type_object\n");
			jobj = json_object_object_get(jobj, key);
			json_parse(jobj);
			break;
			case json_type_array:
				if (!strcmp(key, "Accounts")) {
					json_object *jarray = json_object_object_get(jobj, key);
					parse_accounts(jarray);
				}
				break;
			}
		}
	}
	void parse_accounts(json_object *accs) {
		int acc_len = json_object_array_length(accs);
		json_object *next_obj;

		auto accounts = Base<Enum>::Create();
		for (int i = 0; i < acc_len; i++) {
			next_obj = json_object_array_get_idx(accs, i);
			enum json_type type = json_object_get_type(next_obj);
			if (type != json_type_object) {
				continue;
			}

			string name, path, hdbpath;
			json_object_object_foreach(next_obj, key, val) {
				const char* str_val = json_object_get_string(val);
				if (!strcmp(key, Account_hlpr::TName)) {
					name = str_val;
				} else if (!strcmp(key, Account_hlpr::TFilePath)) {
					path = str_val;
				} else if (!strcmp(key, Account_hlpr::THistoryDBPath)) {
					hdbpath = str_val;
				}
			}
			auto account_impl = Base<AccountImpl>::Create(name, path, hdbpath);
			accounts->AddItem(account_impl);
		}
		accounts.QueryInterface(m_accounts.GetPPtr());
	}

	Boss::RetCode Accounts(Boss::IEnum **res) {
		if (!m_accounts.Get()) {
			throw SettingsException("Error in getting accounts");
		}

		return m_accounts.QueryInterface(res);
	}
	Boss::RetCode AccountsDefault(Boss::IEnum **res) {
		DIR *d;
		ref_ptr<Enum> res_enum = Base<Enum>::Create();
		struct dirent *dir;
		const std::string char_loc = pu_h.SkypeLocation();
		d = opendir(char_loc.c_str());
		if (d)	{
			while ((dir = readdir(d)) != NULL) {
				if (dir->d_type == DT_DIR) { //Directory
					if (!strcmp(dir->d_name, ".")) continue;
					if (!strcmp(dir->d_name, "..")) continue;
					DIR *subd;
					struct dirent *subdir;
					char buf[512];
					sprintf(buf, "%s/%s", char_loc.c_str(), dir->d_name);
					subd = opendir(buf);
					while ((subdir = readdir(subd)) != NULL) {
						if (subdir->d_type == DT_REG && !strcmp(subdir->d_name, "main.db")) {
							res_enum->AddItem(Base<AccountImpl>::Create(dir->d_name, buf, ""));
							break;
						}
					}
					closedir(subd);
				}
			}
			closedir(d);
		}

		return res_enum.QueryInterface(res);
	}

	std::string toString() {
		if (!m_accounts.Get()) {
			throw SettingsException("Error in getting accounts");
		}
		json_object * jobj_settings = json_object_new_object();
		EnumHelper<IAccount> accs_enum(m_accounts);
		json_object *arr = json_object_new_array();
		for (Boss::ref_ptr<IAccount> i = accs_enum.First() ; i.Get() ; i = accs_enum.Next()) {
			Account_hlpr hlpr(i);
			json_object * jobj_acc =  json_object_new_object();
			json_object * jname = json_object_new_string(hlpr.Name().c_str());
			json_object * jpath = json_object_new_string(hlpr.FilePath().c_str());
			json_object * jhdbpath = json_object_new_string(hlpr.HistoryDBPath().c_str());
			json_object_object_add(jobj_acc, Account_hlpr::TName, jname);
			json_object_object_add(jobj_acc, Account_hlpr::TFilePath, jpath);
			json_object_object_add(jobj_acc, Account_hlpr::THistoryDBPath, jhdbpath);

			json_object_array_add(arr, jobj_acc);
		}
		json_object_object_add(jobj_settings, "Accounts", arr);
		std::string res = json_object_to_json_string_ext(jobj_settings, JSON_C_TO_STRING_PLAIN);
		cout << res << endl;

		return res;
	}

	Boss::RetCode AsJsonString(IString **str) {
		if (!m_accounts.Get()) {
			throw SettingsException("Error in getting accounts");
		}
		auto res = Base<String>::Create(toString());
		return res.QueryInterface<IString>(str);
	}

	Boss::RetCode UpdateFromJson(IString *str) {
		if (!m_accounts.Get() || !str) {
			throw SettingsException("Error update from json");
		}
		{ //Close file at filestr destructor
			auto stream = Base<OFileStream>::Create(json_filename);
			string filestr = StringHelper(str).GetString<IString::AnsiString>();
			cout << "Writing str" << filestr << endl;
			if (stream->Write(filestr.c_str(), filestr.length()) != Status::Ok) {
				throw SettingsException("Error update from json");
			}
		}
		loadAccounts();
		return Status::Ok;
	}

	Boss::RetCode update() {
		if (!m_accounts.Get()) {
			throw SettingsException("Error update from json");
		}
		return UpdateFromJson(Base<String>::Create(toString()).Get());
	}

private:
private:
	SettingsImpl *q;

	ref_ptr<IEnum> m_accounts;
	PlatformUtils_hlpr pu_h;
};
const char* SettingsImplPrivate::json_filename = "settings.json";

SettingsImpl::SettingsImpl() {
	p.reset(new SettingsImplPrivate(this));
	cout << "SettingsImpl::SettingsImpl()" << endl;
}

SettingsImpl::~SettingsImpl() {
	// TODO Auto-generated destructor stub
}

RetCode BOSS_CALL SettingsImpl::Update() {
	cout << "SettingsImpl::Update" << endl;
	return p->update();
}

RetCode BOSS_CALL SettingsImpl::AsJsonString(IString **str) {
	cout << "SettingsImpl::AsJsonString" << endl;
	return p->AsJsonString(str);
}

Boss::RetCode BOSS_CALL SettingsImpl::UpdateFromJson(IString *json_string) {
	return p->UpdateFromJson(json_string);
}

Boss::RetCode BOSS_CALL SettingsImpl::Accounts(Boss::IEnum **result) {
	cout << "SettingsImpl::Accounts" << endl;
	return p->Accounts(result);
}

} /* namespace skype_sc */
