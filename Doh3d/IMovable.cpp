#include "PrecompiledHeader.h"
#include "IMovable.h"


namespace Doh3d
{

  bool IMovable::update(float i_dt)
  {
    d_speed += d_accel * i_dt;
    d_position += d_speed * i_dt;

    return true;
  }

} // ns Doh3d
