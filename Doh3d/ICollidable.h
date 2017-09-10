#pragma once

#include "IShape.h"


namespace Doh3d
{

class ICollidable
{
public:

  virtual ~ICollidable() { }

  virtual const IShape* getCollisionShape() const PURE;

};

} // ns Doh3d
