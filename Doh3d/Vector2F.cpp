#include "PrecompiledHeader.h"
#include "Vector2F.h"


namespace Doh3d
{

  Vector2F::Vector2F()
    : Vector2F(0, 0)
  {
  }

  Vector2F::Vector2F(int i_x, int i_y)
    : x((float)i_x), y((float)i_y)
  {
  }

  Vector2F::Vector2F(float i_x, float i_y)
    : x(i_x), y(i_y)
  {
  }


  Vector2F Vector2F::operator+(const Vector2F& i_other) const
  {
    return{ x + i_other.x, y + i_other.y };
  }

  Vector2F Vector2F::operator+=(const Vector2F& i_other)
  {
    x += i_other.x;
    y += i_other.y;
    return *this;
  }

  Vector2F Vector2F::operator-(const Vector2F& i_other) const
  {
    return{ x - i_other.x, y - i_other.y };
  }

  Vector2F Vector2F::operator-=(const Vector2F& i_other)
  {
    x -= i_other.x;
    y -= i_other.y;
    return *this;
  }


  Vector2F Vector2F::operator*(float i_right) const
  {
    return{ x * i_right, y * i_right };
  }

  Vector2F Vector2F::operator*=(float i_right)
  {
    x *= i_right;
    y *= i_right;
    return *this;
  }

  Vector2F Vector2F::operator/(float i_right) const
  {
    return{ x / i_right, y / i_right };
  }

  Vector2F Vector2F::operator/=(float i_right)
  {
    x /= i_right;
    y /= i_right;
    return *this;
  }


} // ns Doh3d
