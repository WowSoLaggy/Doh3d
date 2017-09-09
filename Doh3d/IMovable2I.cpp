#include "PrecompiledHeader.h"
#include "IMovable2I.h"


namespace Doh3d
{

bool IMovable2I::update(float i_dt)
{
  if (!beforeUpdate(i_dt))
    return false;

  d_speed += d_accel * i_dt;
  d_position += d_speed * i_dt;

  if (!afterUpdate(i_dt))
    return false;

  return true;
}

} // ns Doh3d
