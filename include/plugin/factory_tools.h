//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     01.03.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#ifndef __BOSS_PLUGIN_FACTORY_TOOLS_H__
#define __BOSS_PLUGIN_FACTORY_TOOLS_H__

#include "iclass_factory.h"
#include "service_locator_ids.h"
#include "core/ref_obj_qi_ptr.h"
#include "core/error_codes.h"
#include "core/exceptions.h"
#include "common/iservice_locator.h"

namespace Boss
{

  BOSS_DECLARE_RUNTIME_EXCEPTION(FactoryTools)
  
  namespace Private
  {
    ref_ptr<IServiceLocator> GetServiceLocator();
  }
  
  template <typename T>
  inline ref_ptr<T> CreateObject(ClassId clsId)
  {
    auto Locator = Private::GetServiceLocator();
    if (!Locator.Get())
      throw FactoryToolsException("Failed to get ServiceLocator.");
    ref_ptr<IBase> FactoryInst;
    if (Locator->GetService(Service::Locator::Id::ClassFactoryService, FactoryInst.GetPPtr()) != Status::Ok)
      throw FactoryToolsException("ClassFactory not found.");
    qi_ptr<IClassFactory> Factory(FactoryInst);
    if (!Factory.Get())
      throw FactoryToolsException("Interface IClassFactory not found.");
    ref_ptr<IBase> Inst;
    if (Factory->CreateObject(clsId, Inst.GetPPtr()) != Status::Ok)
      throw FactoryToolsException("Failed to create object.");
    qi_ptr<T> Ret(Inst);
    if (!Ret.Get())
      throw FactoryToolsException("Interface not found.");
    return std::move(Ret);
  }
  
}
  
#endif  // !__BOSS_PLUGIN_FACTORY_TOOLS_H__
