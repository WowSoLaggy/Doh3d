#pragma once

#include "Vector2I.h"


namespace Doh3d
{

  class Screen
  {
  public:

    static int getDesktopWidth();
    static int getDesktopHeight();

    static int getClientWidth();
    static int getClientHeight();

    static Vector2I getClientCenter();
    static Vector2I getClientTopLeft();
    static Vector2I getClientRightBottom();

  };

} // ns Doh3d
