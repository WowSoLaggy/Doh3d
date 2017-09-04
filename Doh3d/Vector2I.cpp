#include "PrecompiledHeader.h"
#include "Vector2I.h"


namespace Doh3d
{

  Vector2I::Vector2I()
    : Vector2I(0, 0)
  {
  }

  Vector2I::Vector2I(int i_x, int i_y)
    : x(i_x), y(i_y)
  {
  }

  Vector2I::Vector2I(float i_x, float i_y)
    : x((int)i_x), y((int)i_y)
  {
  }


  Vector2I Vector2I::operator+(const Vector2I& i_other) const
  {
    return{ x + i_other.x, y + i_other.y };
  }

  Vector2I Vector2I::operator+=(const Vector2I& i_other)
  {
    x += i_other.x;
    y += i_other.y;
    return *this;
  }

  Vector2I Vector2I::operator-(const Vector2I& i_other) const
  {
    return{ x - i_other.x, y - i_other.y };
  }

  Vector2I Vector2I::operator-=(const Vector2I& i_other)
  {
    x -= i_other.x;
    y -= i_other.y;
    return *this;
  }


} // ns Doh3d
