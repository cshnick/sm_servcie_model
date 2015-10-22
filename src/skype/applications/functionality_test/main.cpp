#include "../../include/ifaces.h"
#include "../../include/class_ids.h"

#include "plugin/loader.h"
#include <iostream>
#include <unistd.h>

#include <common/string.h>
#include "common/string_helper.h"

#include "cxxabi.h"

using namespace Boss;

int main()
{
  try
  {
    Boss::Loader Ldr("sc_reg.xml", "../lib/" MAKE_MODULE_NAME("service_registry"),
                     "../lib/" MAKE_MODULE_NAME("class_factory"));

    auto ctrl = Boss::CreateObject<skype_sc::IDBController>(skype_sc::service::id::DBControler);
    RefObjQIPtr<skype_sc::IDBWatcher> watcher(ctrl);

    watcher->SetWatchFile(Base<String>::Create("/home/ilia/.Skype/sc.ryabokon.ilia/main.db").Get());

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
