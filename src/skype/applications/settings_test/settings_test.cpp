#include <iostream>
#include "ifaces.h"
#include "iplatformutils.h"
#include "class_ids.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "common/enum.h"
#include "common/file_stream.h"

#include "plugin/module.h"
#include "plugin/loader.h"
#include "skype_helpers.h"

using namespace skype_sc;
using namespace std;
int main (int argc, char **argv) {

	Boss::Loader Ldr("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
					               MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

	try {
		auto pu = CreateObject<IPlatformUtils>(skype_sc::service::id::PlatformUtils);
		ref_ptr<IString> home;
		pu->SkypeLocation(home.GetPPtr());
		cout << StringHelper(home).GetString<IString::AnsiString>() << endl;

		auto settings = CreateObject<ISettings>(skype_sc::service::id::Settings);
		Settings_hlpr sh(settings);

		std::string read_data = sh.AsJsonString();
		cout << "AsJsonString: " << read_data << endl;
		cout << "Accounts count: " <<  sh.Accounts().size() << endl;
		cout << "Default acc index: " << sh.DefaultAccount() << endl;

		cout << "Updating settings" << endl;
		sh.UpdateFromJson(read_data);
		cout << "Succeded!" << endl;

	} catch (const exception &e) {
		cout << e.what() << endl;
	}
	return 0;
}
