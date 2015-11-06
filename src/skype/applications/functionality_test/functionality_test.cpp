#include "../../include/ifaces.h"
#include "../../include/class_ids.h"

#include "plugin/loader.h"
#include <iostream>
#include <unistd.h>

#include <common/string.h>
#include "common/string_helper.h"
#include "core/co_class.h"

#include "cxxabi.h"

#include "ifaces.h"

#ifndef __APPLE__
#   define MAIN_DB__ "/home/ilia/.Skype/sc.ryabokon.ilia/main.db"
#else
#   define MAIN_DB__ "/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db"
#endif

using namespace Boss;
using namespace skype_sc;

struct UIObserver
	:public Boss::CoClass<skype_sc::service::id::DBObserver, IDBObserver> {

	Boss::RetCode BOSS_CALL ReactOnDbChanged(IDBEvent *event) override {
		ref_ptr<IMessage> mesg;
		auto ret = event->Message(mesg.GetPPtr());
		ref_ptr<IString> body;
		if (ret == Status::Ok) ret = mesg->Body(body.GetPPtr());
		int id;
		ret = mesg->Id(&id);
		std::cout << id << " - " << StringHelper(body).GetString<IString::AnsiString>() << std::endl;

		return Boss::Status::Ok;
	}
};

int main()
{
	try  {
		Boss::Loader Ldr("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
				                       MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

		auto ctrl = Boss::CreateObject<skype_sc::IDBController>(skype_sc::service::id::DBControler);
		qi_ptr<skype_sc::IDBWatcher> watcher(ctrl);

		watcher->SetWatchFile(Base<String>::Create(MAIN_DB__).Get());

		ref_ptr<UIObserver> ui_observer = Base<UIObserver>::Create();
		watcher->AddObserver(ui_observer.Get());

		qi_ptr<skype_sc::IService> service(ctrl);
		service->Start();

		while (true) {
			sleep(5);
		}
	} catch (std::exception const &e)  {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
