#pragma once

#include "Vector2I.h"
#include "Vector2F.h"


namespace Doh3d
{

class IShape
{
public:

  ~IShape() { }

  virtual bool containsPoint(const Vector2I& i_point) const PURE;
  virtual bool containsPoint(const Vector2F& i_point) const PURE;

};

} // ns Doh3d
