#pragma once

#include "IInputHandler.h"


namespace Doh3d
{

  class InputPars
  {

  public:

    InputPars()
      : InputPars(1, 1, true, nullptr) { }

    InputPars(float pMouseSensX, float pMouseSensY, bool pMouseAcceleration, IInputHandler* pInputHandler)
      : d_mouseSensX(pMouseSensX)
      , d_mouseSensY(pMouseSensY)
      , d_mouseAcceleration(pMouseAcceleration)
      , d_inputhandler(pInputHandler)
    { }


    float& mouseSensX() { return d_mouseSensX; }
    const float& mouseSensX() const { return d_mouseSensX; }

    float& mouseSensY() { return d_mouseSensY; }
    const float& mouseSensY() const { return d_mouseSensY; }

    bool& mouseAcceleration() { return d_mouseAcceleration; }
    const bool& mouseAcceleration() const { return d_mouseAcceleration; }

    IInputHandler*& inputHandler() { return d_inputhandler; }

  private:

    float d_mouseSensX;				        // Mouse cursor X-axis sensitivity
    float d_mouseSensY;				        // Mouse cursor Y-axis sensitivity

    bool d_mouseAcceleration;         // Indicates whether the mouse acceleration algorithm should be performed on mouse input

    IInputHandler* d_inputhandler;

  };

} // ns Doh3d
