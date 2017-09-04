#include "PrecompiledHeader.h"
#include "Controller.h"

#include "IControlable.h"


namespace Doh3d
{

  Controller::Controller()
    : d_bindedObject(nullptr)
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

} // ns Doh3d
