#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include <memory>

namespace Boss {

  struct ICallback
  {
    virtual ~ICallback()
    {
    }
    virtual void Do() = 0;
  };

  typedef std::shared_ptr<ICallback> ICallbackPtr;

  template <typename TObject>
  class IMemberCallbackImpl : public ICallback {
	  IMemberCallbackImpl(const IMemberCallbackImpl&) = delete;
	  IMemberCallbackImpl& operator=(const IMemberCallbackImpl&) = delete;
  public:
	  typedef void (TObject::*PMethod)();
	  IMemberCallbackImpl(TObject &obj, PMethod mtd)
	  : Obj(obj)
	  , Mtd(mtd) {}
	  virtual void Do() {
		  (Obj.*Mtd)();
	  }

  private:
	  TObject &Obj;
	  PMethod Mtd;
  };

  template <typename TObject>
  ICallbackPtr CreateMemberCallback(TObject &obj, void (TObject::*mtd)()) {
    return ICallbackPtr(new IMemberCallbackImpl<TObject>(obj, mtd));
  }

  template <typename TPFunc>
  class IFuncCallbackImpl : public ICallback  {
	  IFuncCallbackImpl(const IFuncCallbackImpl&) = delete;
	  IFuncCallbackImpl& operator=(const IFuncCallbackImpl&) = delete;
  public:
	  IFuncCallbackImpl(TPFunc *func)
  : Func(func) {}
	  virtual void Do() {
		  Func();
	  }
  private:
	  TPFunc *Func;
  };

  template <typename TFunc>
  ICallbackPtr CreateFuncCallback(TFunc *func) {
    return ICallbackPtr(new IFuncCallbackImpl<TFunc>(func));
  }

} //namespace Boss

#endif  // !__CALLBACK_H__
