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

    if (i_key == DIK_W) d_bindedObject->goUpBegin();
    else if (i_key == DIK_D) d_bindedObject->goRightBegin();
    else if (i_key == DIK_S) d_bindedObject->goDownBegin();
    else if (i_key == DIK_A) d_bindedObject->goLeftBegin();

    return true;
  }

  bool Controller::onKeyUp(Key i_key)
  {
    if (!d_bindedObject)
      return true;

    if (i_key == DIK_W) d_bindedObject->goUpEnd();
    else if (i_key == DIK_D) d_bindedObject->goRightEnd();
    else if (i_key == DIK_S) d_bindedObject->goDownEnd();
    else if (i_key == DIK_A) d_bindedObject->goLeftEnd();

    return true;
  }

} // ns Doh3d
