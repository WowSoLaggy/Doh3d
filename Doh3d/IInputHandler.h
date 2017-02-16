#pragma once

#ifndef INC_DOH3D_IINPUTHANDLER_H
#define INC_DOH3D_IINPUTHANDLER_H


namespace Doh3d
{

  using MouseButton = int;
  using Key = int;


  class IInputHandler
  {
  public:

    virtual bool onMouseMove() { return true; }
    virtual bool onMouseDown(MouseButton pButton) { return true; }
    virtual bool onMouseUp(MouseButton pButton) { return true; }

    virtual bool onKeyPressed(Key pKey) { return true; }
    virtual bool onKeyDown(Key pKey) { return true; }
    virtual bool onKeyUp(Key pKey) { return true; }

  };

} // ns Doh3d


#endif // INC_DOH3D_IINPUTHANDLER_H
