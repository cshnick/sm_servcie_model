//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     01.03.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#ifndef __BOSS_CORE_REF_OBJ_QI_PTR_H__
#define __BOSS_CORE_REF_OBJ_QI_PTR_H__

#include "ref_obj_ptr.h"

namespace Boss
{

  template <typename T>
  class qi_ptr final
  {
  public:
    explicit qi_ptr(T *ptr = 0)
      : Ptr(ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    template <typename Other>
    explicit qi_ptr(Other *ptr)
      : Ptr(0)
    {
      if (ptr)
        ptr->QueryInterface(InterfaceTraits<T>::Id, reinterpret_cast<Boss::Ptr *>(&Ptr));
    }
    qi_ptr(qi_ptr const &ptr)
      : Ptr(ptr.Ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    template <typename Other>
    qi_ptr(qi_ptr<Other> const &ptr)
      : Ptr(0)
    {
      if (ptr.Ptr)
        const_cast<qi_ptr<Other> &>(ptr).QueryInterface(&Ptr);
    }
    qi_ptr(qi_ptr &&ptr)
      : Ptr(ptr.Ptr)
    {
      ptr.Ptr = 0;
    }
    template <typename Other>
    qi_ptr(qi_ptr<Other> &&ptr)
      : Ptr(0)
    {
      if (ptr.Ptr)
        ptr.QueryInterface(&Ptr);
      ptr.Release();
    }
    qi_ptr(ref_ptr<T> const &ptr)
      : Ptr(ptr.Ptr)
    {
      if (Ptr)
        Ptr->AddRef();
    }
    template <typename Other>
    qi_ptr(ref_ptr<Other> const &ptr)
      : Ptr(0)
    {
      if (ptr.Get())
        const_cast<ref_ptr<Other> &>(ptr).QueryInterface(&Ptr);
    }
    qi_ptr(ref_ptr<T> &&ptr)
      : Ptr(ptr.Ptr)
    {
      ptr.Ptr = 0;
    }
    template <typename Other>
    qi_ptr(ref_ptr<Other> &&ptr)
      : Ptr(0)
    {
      if (ptr.Ptr)
        ptr.QueryInterface(&Ptr);
      ptr.Release();
    }
    qi_ptr& operator = (T *ptr)
    {
      qi_ptr Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    template <typename Other>
    qi_ptr& operator = (Other *ptr)
    {
      qi_ptr<T> Tmp;
      if (ptr)
        ptr->QueryInterface(InterfaceTraits<T>::Id, reinterpret_cast<Boss::Ptr *>(Tmp.GetPPtr()));
      Swap(Tmp);
      return *this;
    }
    qi_ptr& operator = (qi_ptr const &ptr)
    {
      qi_ptr Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    template <typename Other>
    qi_ptr& operator = (qi_ptr<Other> const &ptr)
    {
      qi_ptr<T> Tmp;
      if (ptr.Ptr)
        ptr.QueryInterface(Tmp.GetPPtr());
      Swap(Tmp);
      return *this;
    }
    qi_ptr& operator = (qi_ptr &&ptr)
    {
      Release();
      Ptr = ptr.Ptr;
      ptr.Ptr = 0;
      return *this;
    }
    template <typename Other>
    qi_ptr& operator = (qi_ptr<Other> &&ptr)
    {
      qi_ptr<T> Tmp;
      if (ptr.Ptr)
        ptr.QueryInterface(Tmp.GetPPtr());
      Swap(Tmp);
      ptr.Release();
      return *this;
    }
    qi_ptr& operator = (ref_ptr<T> const &ptr)
    {
      qi_ptr Tmp(ptr);
      Swap(Tmp);
      return *this;
    }
    template <typename Other>
    qi_ptr& operator = (ref_ptr<Other> &&ptr)
    {
      qi_ptr<T> Tmp;
      if (ptr.Ptr)
        ptr.QueryInterface(Tmp.GetPPtr());
      Swap(Tmp);
      ptr.Release();
      return *this;
    }
    ~qi_ptr()
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
    void Swap(qi_ptr &ptr)
    {
      T *Tmp = ptr.Ptr;
      ptr.Ptr = Ptr;
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
    operator ref_ptr<T> () const
    {
      return std::move(ref_ptr<T>(Ptr));
    }

  private:
    template <typename Other>
    friend class qi_ptr;
    T *Ptr;
  };

}

#endif  // !__BOSS_CORE_REF_OBJ_QI_PTR_H__
