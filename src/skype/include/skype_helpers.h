/*
 * skype_helpers.h
 *
 *  Created on: 09 ����. 2015 �.
 *      Author: ilia
 */

#ifndef SRC_SKYPE_INCLUDE_SKYPE_HELPERS_H_
#define SRC_SKYPE_INCLUDE_SKYPE_HELPERS_H_

#include "ifaces.h"
#include "iplatformutils.h"

#include "common/string.h"
#include "common/string_helper.h"
#include "core/ref_obj_ptr.h"
#include "core/exceptions.h"
#include "common/enum.h"
#include "common/enum_helper.h"

#include <iostream>

BOSS_DECLARE_RUNTIME_EXCEPTION(SkypeHelpers)
namespace skype_sc {

struct PlatformUtils_hlpr {
	~PlatformUtils_hlpr() {
		std::cout << "PlatformUtils_hlpr" << std::endl;
	}
	PlatformUtils_hlpr(Boss::ref_ptr<IPlatformUtils> p_arg) : m_pu(p_arg) {
	}
	bool Exists(const std::string &fname) {
		auto fname_ref = Base<String>::Create(fname);
		bool ex = false;
		m_pu->Exists(fname_ref.Get(), &ex);
		return ex;
	}
	bool IsFile(const std::string &fname) {
		auto fname_ref = Base<String>::Create(fname);
		bool ex = false;
		m_pu->IsFile(fname_ref.Get(), &ex);
		return ex;
	}
	bool IsDir(const std::string &fname) {
		auto fname_ref = Base<String>::Create(fname);
		bool ex = false;
		m_pu->IsDir(fname_ref.Get(), &ex);
		return ex;
	}
	bool MkPath(const std::string &fname) {
		auto fname_ref = Base<String>::Create(fname);
		bool ok = false;
		m_pu->MkPath(fname_ref.Get(), &ok);
		return ok;
	}
	std::string SkypeLocation() {
		ref_ptr<IString> str;
		m_pu->SkypeLocation(str.GetPPtr());
		return Boss::StringHelper(str).GetString<Boss::IString::AnsiString>();
	}
	std::string UserSettingsDir() {
		ref_ptr<IString> str;
		m_pu->UserSettingsDir(str.GetPPtr());
		return Boss::StringHelper(str).GetString<Boss::IString::AnsiString>();
	}

private:
	mutable ref_ptr<IPlatformUtils> m_pu;
};

struct Account_hlpr {
	Account_hlpr(Boss::ref_ptr<IAccount> p_acc) : m_acc(p_acc) {
	}
	std::string Name() const {
		Boss::ref_ptr<Boss::IString> name;
		m_acc->Name(name.GetPPtr());
		return Boss::StringHelper(name).GetString<Boss::IString::AnsiString>();
	}
	std::string FilePath() const {
		Boss::ref_ptr<Boss::IString> path;
		m_acc->FilePath(path.GetPPtr());
		return Boss::StringHelper(path).GetString<Boss::IString::AnsiString>();
	}
	std::string HistoryDBPath() const {
		Boss::ref_ptr<Boss::IString> path;
		m_acc->HistoryDBPath(path.GetPPtr());
		return Boss::StringHelper(path).GetString<Boss::IString::AnsiString>();
	}
private:
	mutable ref_ptr<IAccount> m_acc;
};

struct Settings_hlpr {
	Settings_hlpr(Boss::ref_ptr<ISettings> p_arg) : m_val(p_arg) {
	}
	std::vector<Account_hlpr> Accounts() {
		ref_ptr<IEnum> accs;
		if (m_val->Accounts(accs.GetPPtr()) != Boss::Status::Ok) {
			throw SkypeHelpersException("Error in Settings_hlpr");
		}
		EnumHelper<IAccount> accsEnum(accs);
		std::vector<Account_hlpr> res;
		for (ref_ptr<IAccount> iter = accsEnum.First(); iter.Get(); iter = accsEnum.Next()) {
			Account_hlpr ah(iter);
			res.push_back(ah);
		}
		return res;
	}
	int DefaultAccount() {
		int res;
		if (m_val->DefaultAccount(&res) != Status::Ok) {
			throw SkypeHelpersException("Error in Settings_hlpr");
		}
		return res;
	}
	std::string AsJsonString() {
		ref_ptr<IString> res;
		if (m_val->AsJsonString(res.GetPPtr()) != Status::Ok) {
			throw SkypeHelpersException("Error in Settings_hlpr");
		}
		return Boss::StringHelper(res).GetString<Boss::IString::AnsiString>();
	}
    void Update() {
    	if (m_val->Update() != Status::Ok) {
    		throw SkypeHelpersException("Error in Settings_hlpr");
    	}
    }
    void UpdateFromJson(const std::string &json) {
    	auto ref_str = Base<String>::Create(json);
    	if (m_val->UpdateFromJson(ref_str.Get()) != Status::Ok) {
    		throw SkypeHelpersException("Error in Settings_hlpr");
    	}
    }

private:
	mutable ref_ptr<ISettings> m_val;
};

struct User_hlpr {
	User_hlpr(Boss::ref_ptr<IUser> p_usr) : m_user(p_usr) {
	}
	ref_ptr<IUser> Get() {
		return m_user;
	}
	std::string Name() const {
		Boss::ref_ptr<Boss::IString> name;
		m_user->Name(name.GetPPtr());
		return Boss::StringHelper(name).GetString<Boss::IString::AnsiString>();

	}
	std::string SkypeName() const {
		Boss::ref_ptr<Boss::IString> skype_name;
		m_user->SkypeName(skype_name.GetPPtr());
		return Boss::StringHelper(skype_name).GetString<Boss::IString::AnsiString>();
	}

private:
	mutable ref_ptr<IUser> m_user;
};
struct Conversation_hlpr {
	Conversation_hlpr(Boss::ref_ptr<IConversation> p_conv) : m_conversation(p_conv) {
	}
	std::vector<User_hlpr> Users() const {
		ref_ptr<IEnum> users;
		m_conversation->Users(users.GetPPtr());
		EnumHelper<IUser> UsersEnum(users);
		std::vector<User_hlpr> res;
		for (ref_ptr<IUser> iter = UsersEnum.First(); iter.Get(); iter = UsersEnum.Next()) {
			User_hlpr uh(iter);
			res.push_back(uh);
		}

		return res;
	}
	std::string Name() {
		Boss::ref_ptr<IString> name;
		m_conversation->Name(name.GetPPtr());
		return Boss::StringHelper(name).GetString<Boss::IString::AnsiString>();
	}
        int Id() {
            int res = -1;
            if (m_conversation->Id(&res) != Boss::Status::Ok) {
                throw SkypeHelpersException("Conversation Id");
            }
            return res;
        }

private:
	mutable ref_ptr<IConversation> m_conversation;
};

struct Message_hlpr {
	Message_hlpr(Boss::ref_ptr<IMessage> messg)
	: m_msg(messg) {

	}

	std::string Author() const {
		Boss::ref_ptr<Boss::IString> author;
		if (m_msg->Author(author.GetPPtr()) != Boss::Status::Ok) {
			throw SkypeHelpersException("Author");
		}
		return Boss::StringHelper(author).GetString<Boss::IString::AnsiString>();
	}
	std::string Body() const {
		Boss::ref_ptr<Boss::IString> body;
		if (m_msg->Body(body.GetPPtr()) != Boss::Status::Ok) {
			throw SkypeHelpersException("Body");
		}
		return Boss::StringHelper(body).GetString<Boss::IString::AnsiString>();
	}
	int Id() const {
		int res = -1;
		if (m_msg->Id(&res) != Boss::Status::Ok) {
			throw SkypeHelpersException("Id");
		}
		return res;
	}
	int SkypeId() const {
		int res = -1;
		if (m_msg->SkypeId(&res) != Boss::Status::Ok) {
			throw SkypeHelpersException("SkypeId");
		}
		return res;
	}
	int Timestamp() const {
		int res = -1;
		if (m_msg->Timestamp(&res) != Boss::Status::Ok) {
			throw SkypeHelpersException("Timestamp");
		}
		return res;
	}
	int SkypeTimestamp() const {
		int res = -1;
		if (m_msg->SkypeTimestamp(&res) != Boss::Status::Ok) {
			throw SkypeHelpersException("SkypeTimestamp");
		}
		return res;
	}
	Conversation_hlpr Conversation() const {
		Boss::ref_ptr<IConversation> conv;
		if (m_msg->Conversation(conv.GetPPtr()) != Boss::Status::Ok) {
			throw SkypeHelpersException("SkypeId");
		}
		Conversation_hlpr hc(conv);

		return hc;
	}

private:
	mutable ref_ptr<IMessage> m_msg;
};

struct DBCtrl_hlpr {
	void Import() {
		if (m_val->Import() != Boss::Status::Ok) {
			throw SkypeHelpersException("Import");
		}
	}

private:
	mutable ref_ptr<IDBController> m_val;
};


} //namespace skype_sc

#endif /* SRC_SKYPE_INCLUDE_SKYPE_HELPERS_H_ */
