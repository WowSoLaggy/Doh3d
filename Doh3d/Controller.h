#pragma once

#include "IInputHandler.h"


namespace Doh3d
{

  class IControlable;
  using ControllerId = int;


  class Controller : public IInputHandler
  {
  public:

    Controller(ControllerId i_id);

    void bindObject(IControlable* i_object);
    void unbindObject();

    int getId() const { return d_id; }


    virtual bool onKeyPressed(Key i_key) override;
    virtual bool onKeyDown(Key i_key) override;
    virtual bool onKeyUp(Key i_key) override;

  private:

    ControllerId d_id;

    IControlable* d_bindedObject;

  };

} // ns Doh3d
