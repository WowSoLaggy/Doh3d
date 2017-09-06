#include "PrecompiledHeader.h"
#include "Controller.h"

#include "IControlable.h"


namespace Doh3d
{

  Controller::Controller(ControllerId i_id)
    : d_id(i_id)
    , d_bindedObject(nullptr)
  {
  }


  void Controller::bindObject(IControlable* i_object)
  {
    if (i_object == d_bindedObject)
      return;

    unbindObject();

    if (!i_object)
      return;

    d_bindedObject = i_object;
  }

  void Controller::unbindObject()
  {
    if (d_bindedObject)
      d_bindedObject = nullptr;
  }


  void Controller::clearBindings()
  {
    d_actionMap.clear();
  }

  void Controller::bindKey(Key i_key, Action i_action)
  {
    d_actionMap[i_key] = i_action;
  }


  bool Controller::onKeyPressed(Key i_key)
  {
    if (!d_bindedObject)
      return true;

    return true;
  }

  bool Controller::onKeyDown(Key i_key)
  {
    if (!d_bindedObject)
      return true;

    auto it = d_actionMap.find(i_key);
    if (it == d_actionMap.end())
      return true;

    Action action = it->second;

    switch (action)
    {
    case Action::GoUp: d_bindedObject->goUpBegin(); break;
    case Action::GoRight: d_bindedObject->goRightBegin(); break;
    case Action::GoDown: d_bindedObject->goDownBegin(); break;
    case Action::GoLeft: d_bindedObject->goLeftBegin(); break;
    }

    return true;
  }

  bool Controller::onKeyUp(Key i_key)
  {
    if (!d_bindedObject)
      return true;

    auto it = d_actionMap.find(i_key);
    if (it == d_actionMap.end())
      return true;

    Action action = it->second;

    switch (action)
    {
    case Action::GoUp: d_bindedObject->goUpEnd(); break;
    case Action::GoRight: d_bindedObject->goRightEnd(); break;
    case Action::GoDown: d_bindedObject->goDownEnd(); break;
    case Action::GoLeft: d_bindedObject->goLeftEnd(); break;
    }

    return true;
  }

} // ns Doh3d
