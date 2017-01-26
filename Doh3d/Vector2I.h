#pragma once

#ifndef INC_DOH3D_VECTOR2_H
#define INC_DOH3D_VECTOR2_H


namespace Doh3d
{

  class Vector2I
  {
  public:

    Vector2I(int pX, int pY);
    Vector2I(float pX, float pY);

    int& x() { return d_x; }
    const int& x() const { return d_x; }

    int& y() { return d_y; }
    const int& y() const { return d_y; }


    static Vector2I empty();
    static Vector2I identity();


  private:

    int d_x;
    int d_y;

  };

} // ns Doh3d


#endif // INC_DOH3D_VECTOR2_H
