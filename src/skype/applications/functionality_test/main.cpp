#include "../../include/ifaces.h"
#include "../../include/class_ids.h"

#include "plugin/loader.h"
#include <iostream>

int main()
{
  try
  {
    Boss::Loader Ldr("sc_reg.xml", "./" MAKE_MODULE_NAME("service_registry"),
                     "./" MAKE_MODULE_NAME("class_factory"));
    auto serv = Boss::CreateObject<skype_sc::IDBWatcher>(skype_sc::service::id::DBWatcher);
    serv->AddObserver();
    Boss::RefObjQIPtr<skype_sc::IService> service(serv);
    service->Start();

//    auto Obj1 = Boss::CreateObject<MyNs::IFace1>(MyNs::Service::Id::Face1);
//    if (Obj1->Method() != Boss::Status::Ok)
//      std::cerr << "Failed to call IFace1::Method" << std::endl;
//    auto Obj2 = Boss::CreateObject<MyNs::IFace2>(MyNs::Service::Id::Face2);
//    if (Obj2->Method() != Boss::Status::Ok)
//      std::cerr << "Failed to call IFace2::Method" << std::endl;
  }
  catch (std::exception const &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
