#include <iostream>
#include "ifaces.h"
#include "iplatformutils.h"
#include "class_ids.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "common/enum.h"
#include "common/file_stream.h"
#include "common/sm_debug.h"

#include "plugin/module.h"
#include "plugin/loader.h"
#include "skype_helpers.h"

using namespace skype_sc;
using namespace std;
using namespace sm;

int main (int argc, char **argv) {

	Boss::Loader Ldr(split_argv0(argv[0]).first + "/" + "sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
																      MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

	try {
		//Test PlatformUtils first
		dcout << "Start settings test" << endl;
		auto pu = CreateObject<IPlatformUtils>(skype_sc::service::id::PlatformUtils);
		PlatformUtils_hlpr pu_h(pu);
		string skype_location = pu_h.SkypeLocation();
		string user_settings_dir = pu_h.UserSettingsDir();
		
		dcout <<"Skype location: " << skype_location << "; exists: " << pu_h.Exists(skype_location) << endl;
		dcout <<"UserSettingsDir: " << user_settings_dir << endl;
		dcout <<"\tIs directory: " << pu_h.IsDir(user_settings_dir) << endl;
		dcout <<"\tIs file: " << pu_h.IsFile(user_settings_dir) << endl;
		auto file_children = pu_h.Children(skype_location);
		dcout <<"Request children for: " << skype_location << endl;
		for (auto file : file_children) {
			dcout <<"\tNext child: " << file << endl;
		}

		//Test Settings
		auto settings = CreateObject<ISettings>(skype_sc::service::id::Settings);
		Settings_hlpr sh(settings);

		std::string read_data = sh.AsJsonString();
		dcout <<"AsJsonString: " << read_data << endl;
		dcout <<"Accounts count: " <<  sh.Accounts().size() << endl;
		dcout <<"Default acc index: " << sh.DefaultAccount() << endl;

		dcout <<"Updating settings" << endl;
		sh.UpdateFromJson(read_data);
		dcout <<"Succeded!" << endl;

	} catch (const exception &e) {
		dcout <<e.what() << endl;
	}
	return 0;
}
