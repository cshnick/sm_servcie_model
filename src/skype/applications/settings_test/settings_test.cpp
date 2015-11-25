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
		cout << "Json resource: " << read_data << endl;

		std::string test_data = "/home/user/.local";
		auto pos = read_data.find_last_of("HistoryDBPath");
		pos += 4;
		read_data.insert(read_data.begin() + pos, test_data.begin(), test_data.end());

		cout << "Json result: " << read_data << endl;
		sh.UpdateFromJson(read_data);
		cout << "After update" << sh.AsJsonString() << endl;

		//		sz->Save(Base<OFileStream>::Create("settings.json").Get());
//		sz->Load(Base<OFileStream>::Create("settings.json").Get());


	} catch (const exception &e) {
		cout << e.what() << endl;
	}
	return 0;
}
