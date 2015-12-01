#include "../../include/ifaces.h"
#include "../../include/class_ids.h"

#include "plugin/loader.h"
#include <iostream>
#include <unistd.h>

#include <common/string.h>
#include "common/string_helper.h"
#include "common/ienum.h"
#include "common/enum.h"
#include "common/enum_helper.h"
#include "core/co_class.h"
#include "core/ref_obj_ptr.h"
#include "core/base.h"
#include "core/ibase.h"
#include "skype_helpers.h"

#include "cxxabi.h"

#include "ifaces.h"

#ifndef __APPLE__
#   define MAIN_DB__ "/home/ilia/.Skype/luxa_ryabic/main.db"
#else
#   define MAIN_DB__ "/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db"
#endif

BOSS_DECLARE_RUNTIME_EXCEPTION(FunctionalityTest)

using namespace Boss;
using namespace skype_sc;

struct UIObserver
	:public Boss::CoClass<skype_sc::service::id::DBObserver, IDBObserver> {

	Boss::RetCode BOSS_CALL ReactOnDbChanged(IDBEvent *event) override {
		ref_ptr<IMessage> mesg;
		if (event->Message(mesg.GetPPtr()) != Status::Ok) {
			throw FunctionalityTestException("Error getting message");
		}
		Message_hlpr msg_hlpr(mesg);
		std::cout << msg_hlpr.SkypeId() << " - " << msg_hlpr.Body() << std::endl;

		return Boss::Status::Ok;
	}
};

int main()
{
	try  {
		Boss::Loader Ldr("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
				                       MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

		auto pu = PlatformUtils_hlpr(CreateObject<IPlatformUtils>(skype_sc::service::id::PlatformUtils));

		pu.MkPath("skype/sc.ryabokon.ilia");
		pu.MkPath("skype/luxa_ryabic");

		auto ctrl = CreateObject<IDBController>(skype_sc::service::id::DBControler);
		qi_ptr<skype_sc::IDBWatcher> watcher(ctrl);


		std::string first_skype = "/home/ilia/.Skype/sc.ryabokon.ilia/main.db", first_history = "skype/sc.ryabokon.ilia";
		std::cout << "Initial data: \n" << "\tSkype: " << first_skype << "\n\tHistory: " << first_history << std::endl;
		watcher->SetWatchFile(Base<String>::Create(first_skype).Get());
		ctrl->SetDBPath(Base<String>::Create(first_history).Get());

		ref_ptr<UIObserver> ui_observer = Base<UIObserver>::Create();
		watcher->AddObserver(ui_observer.Get());

		qi_ptr<skype_sc::IService> service(ctrl);

		service->Start();

		ref_ptr<IEnum> recent;
		ctrl->Recent(recent.GetPPtr());
		int counter = 0;
		EnumHelper<IMessage> mess_enum(recent);
		for (ref_ptr<IMessage> iter = mess_enum.First(); iter.Get(); iter = mess_enum.Next()) {
			Message_hlpr mh(iter);
			std::cout << "Body: " << mh.Body() << "; Id: " << mh.Id() << std::endl;
			counter++;
		}
		std::cout << "Counter: " << counter << std::endl;

		sleep(10);

		std::string second_skype = MAIN_DB__, second_history = "skype/luxa_ryabic";
		std::cout << "Initial data: \n" << "\tSkype: " << second_skype << "\tHistory: " << second_history << std::endl;
		service->Restart(Base<String>::Create(second_skype).Get(), Base<String>::Create(second_history).Get());
		std::cout << "Reseted; wait for events" << std::endl;
		sleep(10);
		service->Stop();
		std::cout << "Stopped" << std::endl;
//		while (true) {
//			sleep(5);
//		}
	} catch (std::exception const &e)  {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "Succeeded!" << std::endl;

	return 0;
}
