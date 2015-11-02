#include "../../include/ifaces.h"
#include "../../include/class_ids.h"

#include "plugin/loader.h"
#include <iostream>
#include <unistd.h>

#include <common/string.h>
#include "common/string_helper.h"

#include "cxxabi.h"

#ifndef __APPLE__
#   define MAIN_DB__ "/home/ilia/.Skype/sc.ryabokon.ilia/main.db"
#else
#   define MAIN_DB__ "/Users/ilia/Library/Application Support/Skype/sc.ryabokon.ilia/main.db"
#endif

using namespace Boss;

int main()
{
  try
  {
    Boss::Loader Ldr("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
                     MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory"));

    auto ctrl = Boss::CreateObject<skype_sc::IDBController>(skype_sc::service::id::DBControler);
    RefObjQIPtr<skype_sc::IDBWatcher> watcher(ctrl);

    watcher->SetWatchFile(Base<String>::Create(MAIN_DB__).Get());

    Boss::RefObjQIPtr<skype_sc::IService> service(watcher);
    service->Start();

    RefObjPtr<IString> str;

    while (true) {
    	sleep(5);
    }
  }
  catch (std::exception const &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
