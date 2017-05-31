#pragma once

#ifndef INC_DOH3D_SCREEN_H
#define INC_DOH3D_SCREEN_H


#include "Position2.h"


namespace Doh3d
{

  class Screen
  {
  public:

    static int getDesktopWidth();
    static int getDesktopHeight();

    static int getClientWidth();
    static int getClientHeight();

    static Position2 getClientCenter();
    static Position2 getClientTopLeft();
    static Position2 getClientRightBottom();

  };

} // ns Doh3d


#endif // INC_DOH3D_SCREEN_H
