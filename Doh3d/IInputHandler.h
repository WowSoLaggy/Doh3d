#pragma once

#ifndef INC_DOH3D_IINPUTHANDLER_H
#define INC_DOH3D_IINPUTHANDLER_H


namespace Doh3d
{

  class IInputHandler
  {
  public:

    // TODO: change "int pButton" to typedefs
    virtual bool onMouseMove() PURE;
    virtual bool onMouseDown(int pButton) PURE;
    virtual bool onMouseUp(int pButton) PURE;

    virtual bool onKeyPressed(int pKey) PURE;
    virtual bool onKeyDown(int pKey) PURE;
    virtual bool onKeyUp(int pKey) PURE;

  };

} // ns Doh3d


#endif // INC_DOH3D_IINPUTHANDLER_H
