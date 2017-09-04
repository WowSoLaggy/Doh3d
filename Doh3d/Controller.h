#pragma once


namespace Doh3d
{

  class IControlable;

  class Controller
  {
  public:

    Controller();

    void bindObject(IControlable* i_object);
    void unbindObject();

  private:

    IControlable* d_bindedObject;

  };

} // ns Doh3d
