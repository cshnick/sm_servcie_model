#include <iostream>
#include <future>

#include "common/filewatcher.h"
#include "common/time_calculator.h"
#include "common/sm_debug.h"
#include "plugin/loader.h"
#include "skype_helpers.h"
#include "ifaces.h"
#include "class_ids.h"

using namespace Boss;
using namespace std;
using namespace sm;
using namespace skype_sc;

int main (int argc, char **argv) {
	Boss::Loader Ldr(split_argv0(argv[0]).first + "/sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
                                                                 MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

	auto settings = CreateObject<ISettings>(skype_sc::service::id::Settings);
	Settings_hlpr sh(settings);

	uint64 ct = 0;
	auto accs = sh.Accounts();
	for (Account_hlpr a : accs) {
		sm::filewatcher fw(a.FilePath(), [](const std::string &path, int) {
			dcout << "Callback retrieved, incoming path: " << path << std::endl;
		});
		dcout << "Attempting to start filewatcher" << endl;
		fw.start();
		dcout << "fw.start() returned, catching events" << endl;
		sm::sleep(30 * 1000);
		dcout << "Attempting to stop filewatcher" << endl;
		ct = GetTimeMs64();
		fw.stop();
		dcout << "fw.stop() returned, elapsed time " << GetTimeMs64() - ct << "; catching events stopped. Ensuring stop watching" << endl;
		ct = GetTimeMs64();
		sm::sleep(30 * 1000);
		dcout << "Finished, cleaning thread" << endl;
	}
    dcout << "Cleaning finished; elapsed time: " << human_readable(GetTimeMs64() - ct) << endl;
	    
    return 0;
}
