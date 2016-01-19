#include "../../include/ifaces.h"
#include "../../include/class_ids.h"

#include "plugin/loader.h"
#include <iostream>
#include <fstream>
//#include <unistd.h>


#include <common/string.h>
#include "common/string_helper.h"
#include "common/ienum.h"
#include "common/enum.h"
#include "common/enum_helper.h"
#include "common/sm_debug.h"
#include "core/co_class.h"
#include "core/ref_obj_ptr.h"
#include "core/base.h"
#include "core/ibase.h"
#include "skype_helpers.h"
#include "core/exceptions.h"

//#include "cxxabi.h"
#include "ifaces.h"

BOSS_DECLARE_RUNTIME_EXCEPTION(FunctionalityTest)

using namespace Boss;
using namespace skype_sc;
using namespace std;
using namespace sm;

struct UIObserver
	:public Boss::CoClass<skype_sc::service::id::DBObserver, IDBObserver> {

	Boss::RetCode BOSS_CALL ReactOnDbChanged(IDBEvent *event) override {
		ref_ptr<IMessage> mesg;
		if (event->Message(mesg.GetPPtr()) != Status::Ok) {
			throw FunctionalityTestException("Error getting message");
		}
		Message_hlpr msg_hlpr(mesg);
		dcout << msg_hlpr.SkypeId() << " - " << msg_hlpr.Body() << endl;

		return Boss::Status::Ok;
	}
};

int main()
{
	try  {
//		ofstream fstr("functionality_test.log");
//		cout.rdbuf(fstr.rdbuf());

		Boss::Loader Ldr("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
				                       MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

		auto pu = PlatformUtils_hlpr(CreateObject<IPlatformUtils>(skype_sc::service::id::PlatformUtils));
    	auto ctrl = CreateObject<IDBController>(skype_sc::service::id::DBControler);
		qi_ptr<skype_sc::IDBWatcher> watcher(ctrl);

		auto settings = CreateObject<ISettings>(skype_sc::service::id::Settings);
		Settings_hlpr seh(settings);

		string first_skype = seh.Accounts().at(0).FilePath(), first_history = seh.Accounts().at(0).HistoryDBPath();
		dcout << "Initial data: \n" << "\tSkype: " << first_skype << "\n\tHistory: " << first_history << endl;
		watcher->SetWatchFile(Base<String>::Create(first_skype).Get());
		ctrl->SetDBPath(Base<String>::Create(first_history).Get());

		ref_ptr<UIObserver> ui_observer = Base<UIObserver>::Create();
		watcher->AddObserver(ui_observer.Get());

		qi_ptr<skype_sc::IService> service(ctrl);
		service->Start();

		dcout << "Get async messages for " << first_skype << endl;
		ctrl->GetMessagesAsync([](IMessage *m, int progress) {
			ref_ptr<IMessage>pm(m);
			skype_sc::Message_hlpr mes_h(pm);
			dcout << "\r\t" << mes_h.Id() << " : " << mes_h.Body() << " - " << progress  << "%";
		}, nullptr);
		dcout << endl;

//		sleep(1);

		string second_skype = seh.Accounts().at(1).FilePath(), second_history = seh.Accounts().at(1).HistoryDBPath();
		dcout << "Initial data: \n" << "\tSkype: " << second_skype << "\tHistory: " << second_history << endl;
		dcout << "Prepairing to restart..." << endl;
		service->Restart(Base<String>::Create(second_skype).Get(), Base<String>::Create(second_history).Get());
		dcout << "Restarted; get async messages for " << second_skype << endl;
		ctrl->GetMessagesAsync([](IMessage *m, int progress) {
			ref_ptr<IMessage>pm(m);
			skype_sc::Message_hlpr mes_h(pm);
			dcout << "\r\t" << mes_h.Id() << " : " << mes_h.Body()  << " - " << progress  << "%";
		} , nullptr);
		dcout << endl;
//		sleep(10);
		service->Stop();
		dcout << "Stopped" << endl;
//		while (true) {
//			sleep(5);
//		}
	} catch (exception const &e)  {
		cerr << "Error: " << e.what() << endl;
	}

	dcout << "Succeeded!" << endl;

	return 0;
}
