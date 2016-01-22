//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     01.03.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#ifndef __BOSS_PLUGIN_LOADER_H__
#define __BOSS_PLUGIN_LOADER_H__

#include "iservice_registry.h"
#include "iclass_factory.h"
#include "iclass_factory_ctrl.h"
#include "module_holder.h"
#include "module.h"
#include "service_ids.h"
#include "core/exceptions.h"
#include "core/base.h"
#include "common/service_locator.h"
#include "common/file_stream.h"
#include "common/iserializable.h"

#include <string>

#define SM_DEBUG_POSTFIX ""
#if (defined(_WIN32) && defined(_DEBUG))
#	define SM_DEBUG_POSTFIX "d"
#endif
#ifdef _WIN32
#   define MAKE_MODULE_NAME(name_) name_ SM_DEBUG_POSTFIX".dll"
#   define MAKE_MODULE_PATH ""
#elif (defined(__SM_QTCREATOR__))
#   define MAKE_MODULE_NAME(name_) "lib" name_ ".so"
#   define MAKE_MODULE_PATH "../cmake_sm/lib/"
#elif (defined(__linux__) || defined(__unix__))
#   define MAKE_MODULE_NAME(name_) "lib" name_ ".so"
#   define MAKE_MODULE_PATH "../lib/"
#elif (defined(__APPLE__))
#   define MAKE_MODULE_NAME(name_) "lib" name_ ".dylib"
#   define MAKE_MODULE_PATH "../../lib/Debug/"
#else
#    error "Unknown OS"
#endif

namespace Boss
{

  BOSS_DECLARE_RUNTIME_EXCEPTION(Loader)
  
  class Loader final
  {
  public:
    Loader(Loader const &) = delete;
    Loader& operator = (Loader const &) = delete;
    
    Loader(std::string const &registryFilePath,
           std::string const &srvRegModulePath,
           std::string const &clsFactoryModulePath)
      : Locator(Base<ServiceLocator>::Create())
      , SrvRegistry([&] ()
          {
            auto SrvRegModule = std::move(ModuleHolder(std::move(DllHolder(srvRegModulePath))));
            auto SrvReg = SrvRegModule.CreateObject<IServiceRegistry>(Service::Id::ServiceRegistry);
            qi_ptr<ISerializable> Serializable(SrvReg);
            if (!Serializable.Get())
              throw LoaderException("Failed to get ISerializable interface from Registry object.");
            if (Serializable->Load(Base<IFileStream>::Create(registryFilePath).Get()) != Status::Ok)
              throw LoaderException("Failed to load Registry.");
            return std::move(std::make_pair(std::move(SrvRegModule), std::move(SrvReg)));
          } ())
      , ClsFactory([&] ()
          {
            auto ClassFactoryModule = std::move(ModuleHolder(std::move(DllHolder(clsFactoryModulePath))));
            auto NewClsFactory = ClassFactoryModule.CreateObject<IClassFactory>(Service::Id::ClassFactory);
            qi_ptr<IClassFactoryCtrl> Ctrl(NewClsFactory);
            if (!Ctrl.Get())
              throw LoaderException("Failed to get ICalssFactoryCtrl interface from ClassFactory object.");
            if (Ctrl->SetRegistry(SrvRegistry.second.Get()) != Status::Ok)
              throw LoaderException("Failed to set Registry into ClassFactory.");
            ClassFactoryModule.SetServiceLocator(Locator.Get());
            return std::move(std::make_pair(std::move(ClassFactoryModule), std::move(NewClsFactory)));
          } ())
    {
      if (Locator->AddService(Service::Locator::Id::ClassFactoryService,
          qi_ptr<IBase>(ClsFactory.second).Get()) != Status::Ok)
      {
        throw LoaderException("Failed to put ClassFactory into ServiceLocator.");
      }
      Private::SetServiceLocator(Locator.Get());
    }
    template <typename T>
    ref_ptr<T> CreateObject(ClassId clsId)
    {
      ref_ptr<IBase> NewInst;
      if (ClsFactory.second->CreateObject(clsId, NewInst.GetPPtr()) != Status::Ok)
        throw LoaderException("Failed to create object.");
      qi_ptr<T> Ret(NewInst);
      if (!Ret.Get())
        throw LoaderException("Interface not found.");
      return Ret;
    }
    ~Loader()
    {
      Locator->DelService(Service::Locator::Id::ClassFactoryService);
      ClsFactory.second.Release();
      SrvRegistry.second.Release();
      Private::SetServiceLocator(0);
    }
    
  private:
    ref_ptr<IServiceLocator> Locator;
    std::pair<ModuleHolder, ref_ptr<IServiceRegistry>> SrvRegistry;
    std::pair<ModuleHolder, ref_ptr<IClassFactory>> ClsFactory;
  };
  
}

#endif  // !__BOSS_PLUGIN_LOADER_H__
