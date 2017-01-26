#include "Doh3d.h"
#include "Vector2I.h"


namespace Doh3d
{

  Vector2I::Vector2I(int pX, int pY)
    : d_x(pX), d_y(pY)
  { }

  Vector2I::Vector2I(float pX, float pY)
    : d_x((int)pX), d_y((int)pY)
  { }


  Vector2I Vector2I::empty() { return Vector2I(0, 0); }
  Vector2I Vector2I::identity() { return Vector2I(1, 1); }


} // ns Doh3d
