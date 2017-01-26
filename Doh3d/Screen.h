#pragma once

#ifndef INC_DOH3D_SCREEN_H
#define INC_DOH3D_SCREEN_H


namespace Doh3d
{

  class Screen
  {
  public:

    static int getDesktopWidth();
    static int getDesktopHeight();

    static int getClientWidth();
    static int getClientHeight();

    static D3DXVECTOR2 getClientCenter();

  };

} // ns Doh3d


#endif // INC_DOH3D_SCREEN_H
