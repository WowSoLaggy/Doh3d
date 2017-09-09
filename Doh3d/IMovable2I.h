#pragma once

#include "IPositioned2I.h"


namespace Doh3d
{

class IMovable2I
  : public IPositioned2I
{

public:

  const Vector2I& getSpeed() const { return d_speed; }
  void setSpeed(const Vector2I& i_speed) { d_speed = i_speed; }

  const Vector2I& getAccel() const { return d_accel; }
  void setAccel(const Vector2I& i_accel) { d_accel = i_accel; }

  bool update(float i_dt);

protected:

  Vector2I d_speed;
  Vector2I d_accel;

  virtual bool beforeUpdate(float i_dt) { return true; }
  virtual bool afterUpdate(float i_dt) { return true; }

};

} // ns Doh3d
