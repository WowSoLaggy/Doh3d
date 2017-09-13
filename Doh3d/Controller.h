#pragma once

#include "IInputHandler.h"
#include "Actions.h"


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

    void clearBindings();
    void bindKey(Key i_key, Action i_action);


    virtual bool onKeyPressed(Key i_key) override;
    virtual bool onKeyDown(Key i_key) override;
    virtual bool onKeyUp(Key i_key) override;

  private:

    ControllerId d_id;

    IControlable* d_bindedObject;

    std::unordered_map<Key, Action> d_actionMapKeyboard;

  };

} // ns Doh3d
