#pragma once

#ifndef INC_DOH3D_SCREEN_H
#define INC_DOH3D_SCREEN_H


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


#endif // INC_DOH3D_SCREEN_H
