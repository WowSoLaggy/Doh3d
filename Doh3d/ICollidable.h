#pragma once

#include "IShape.h"


namespace Doh3d
{

class ICollidable
{
public:

  ICollidable();
  virtual ~ICollidable();

  const IShape* getCollisionShape() const { return d_collisionShape; }

  void setCollisionShape(const IShape* i_shape);
  void resetCollisionShape();

private:

  const IShape* d_collisionShape;

};

} // ns Doh3d
