#include "PrecompiledHeader.h"
#include "Circle.h"


namespace Doh3d
{

Circle::Circle(const Vector2F& i_center, float i_radius)
  : d_center(i_center)
  , d_radius(i_radius)
  , d_radiusSq(i_radius * i_radius)
{
}


bool Circle::containsPoint(const Vector2I& i_point) const
{
  return (i_point - d_center).lengthSq() <= d_radiusSq;
}

bool Circle::containsPoint(const Vector2F& i_point) const
{
  return (i_point - d_center).lengthSq() <= d_radiusSq;
}

} // ns Doh3d
