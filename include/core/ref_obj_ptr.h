//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     01.03.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#ifndef __BOSS_CORE_REF_OBJ_PTR_H__
#define __BOSS_CORE_REF_OBJ_PTR_H__

#include "core_types.h"
#include "error_codes.h"
#include "utils.h"

namespace Boss
{

  template <typename T>
  class qi_ptr;

  template <typename T>
  class ref_ptr final
  {
  public:
    explicit ref_ptr(T *ptr = nullptr)
      : Ptr(ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    template <typename Other>
    explicit ref_ptr(T *ptr)
      : Ptr(ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    ref_ptr(ref_ptr const &ptr)
      : Ptr(ptr.Ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    template <typename Other>
    ref_ptr(ref_ptr<Other> const &ptr)
      : Ptr(ptr.Ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    ref_ptr(ref_ptr &&ptr)
      : Ptr(ptr.Ptr)
    {
      ptr.Ptr = 0;
    }
    template <typename Other>
    ref_ptr(ref_ptr<Other> &&ptr)
      : Ptr(ptr.Ptr)
    {
      ptr.Ptr = 0;
    }
    ref_ptr& operator = (T *ptr)
    {
      ref_ptr Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    template <typename Other>
    ref_ptr& operator = (Other *ptr)
    {
      ref_ptr<Other> Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    ref_ptr& operator = (ref_ptr const &ptr)
    {
      ref_ptr Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    template <typename Other>
    ref_ptr& operator = (ref_ptr<Other> const &ptr)
    {
      ref_ptr<Other> Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    ref_ptr& operator = (ref_ptr &&ptr)
    {
      Release();
      Ptr = ptr.Ptr;
      ptr.Ptr = 0;
      return *this;
    }
    template <typename Other>
    ref_ptr& operator = (ref_ptr<Other> &&ptr)
    {
      Release();
      Ptr = ptr.Ptr;
      ptr.Ptr = 0;
      return *this;
    }
    ~ref_ptr()
    {
      Release();
    }
    UInt AddRef()
    {
      return Ptr ? Ptr->AddRef() : 0;
    }
    UInt Release()
    {
      UInt Ret = 0;
      if (Ptr)
        Ret = Ptr->Release();
      Ptr = 0;
      return Ret;
    }
    template <typename IFace>
    RetCode QueryInterface(IFace **iface)
    {
      return !Ptr ? Status::Fail :
        Ptr->QueryInterface(InterfaceTraits<IFace>::Id,
          reinterpret_cast<Boss::Ptr *>(iface));
    }
    T* Get()
    {
      return Ptr;
    }
    T const* Get() const
    {
      return Ptr;
    }
    T** GetPPtr()
    {
      return &Ptr;
    }
    void Swap(ref_ptr &ptr)
    {
      T *Tmp = ptr.Ptr;
      ptr.Ptr = Ptr;
      Ptr = Tmp;
    }
    template <typename Other>
    void Swap(ref_ptr<Other> &ptr)
    {
      auto *Tmp = ptr.Ptr;
      ptr.Ptr = static_cast<decltype(ptr.Ptr)>(Ptr);
      Ptr = Tmp;
    }
    T* operator -> ()
    {
      return Ptr;
    }
    T const* operator -> () const
    {
      return Ptr;
    }

  private:
    template <typename Other>
    friend class ref_ptr;
    template <typename Other>
    friend class qi_ptr;
    
    T *Ptr;
  };

}

#endif  // !__BOSS_CORE_REF_OBJ_PTR_H__
