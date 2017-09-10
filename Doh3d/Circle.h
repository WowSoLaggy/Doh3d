#pragma once

#include "IShape.h"
#include "Vector2F.h"


namespace Doh3d
{

class Circle : public IShape
{
public:

  Circle(const Vector2F& i_center, float i_radius);
  virtual ~Circle() { }

  virtual bool containsPoint(const Vector2I& i_point) const override;
  virtual bool containsPoint(const Vector2F& i_point) const override;

private:

  Vector2F d_center;
  float d_radius;
  float d_radiusSq;

};

} // ns Doh3d
