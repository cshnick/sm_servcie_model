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

BOSS_DECLARE_RUNTIME_EXCEPTION(SkypeHelpers)
namespace skype_sc {

struct PlatformUtils_hlpr {
	PlatformUtils_hlpr(Boss::ref_ptr<IPlatformUtils> p_arg) : m_pu(p_arg) {
	}
	bool Exists(const std::string &fname) {
		auto fname_ref = Base<String>::Create(fname);
		bool ex = false;
		m_pu->Exists(fname_ref.Get(), &ex);
		return ex;
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
	constexpr static const char* TName = "Name";
	constexpr static const char* TFilePath = "FilePath";
	constexpr static const char* THistoryDBPath = "HistoryDBPath";
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
		EnumHelper<IAccount> en_h(accs);
		std::vector<Account_hlpr> res;
		for (ref_ptr<IAccount> iter = en_h.First(); accs.Get(); iter = en_h.Next()) {
			Account_hlpr ah(iter);
			res.push_back(ah);
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
		m_conversation.QueryInterface(users.GetPPtr());
		EnumHelper<IUser> UsersEnum(users);
		std::vector<User_hlpr> res;
		for (ref_ptr<IUser> iter = UsersEnum.First(); users.Get(); iter = UsersEnum.Next()) {
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

private:
	mutable ref_ptr<IConversation> m_conversation;
};

struct Message_hlpr {
	Message_hlpr(Boss::ref_ptr<IMessage> messg)
	: m_msg(messg) {

	}

	std::string Author() const {
		Boss::ref_ptr<Boss::IString> author;
		m_msg->Author(author.GetPPtr());
		return Boss::StringHelper(author).GetString<Boss::IString::AnsiString>();
	}
	std::string Body() const {
		Boss::ref_ptr<Boss::IString> body;
		m_msg->Body(body.GetPPtr());
		return Boss::StringHelper(body).GetString<Boss::IString::AnsiString>();
	}
	int Id() const {
		int res = -1;
		m_msg->Id(&res);
		return res;
	}
	int Timestamp() const {
		int res = -1;
		m_msg->Timestamp(&res);
		return res;
	}
	int SkypeTimestamp() const {
		int res = -1;
		m_msg->SkypeTimestamp(&res);
		return res;
	}
        Conversation_hlpr Conversation() const {
		Boss::ref_ptr<IConversation> conv;
		m_msg->Conversation(conv.GetPPtr());
		Conversation_hlpr hc(conv);

		return hc;
	}

private:
	mutable ref_ptr<IMessage> m_msg;
};


} //namespace skype_sc

#endif /* SRC_SKYPE_INCLUDE_SKYPE_HELPERS_H_ */
