#include "PrecompiledHeader.h"
#include "ICollidable.h"


namespace Doh3d
{

ICollidable::ICollidable()
  : d_collisionShape(nullptr)
{
}

ICollidable::~ICollidable()
{
  resetCollisionShape();
}


void ICollidable::setCollisionShape(const IShape* i_shape)
{
  if (i_shape == d_collisionShape)
    return;

  resetCollisionShape();

  if (!i_shape)
    return;

  d_collisionShape = i_shape;
}

void ICollidable::resetCollisionShape()
{
  if (d_collisionShape)
  {
    delete d_collisionShape;
    d_collisionShape = nullptr;
  }
}

} // ns Doh3d
