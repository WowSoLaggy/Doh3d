#pragma once

#include "IPositioned2F.h"


namespace Doh3d
{

  class IMovable2F
    : public IPositioned2F
  {

  public:

    const Vector2F& getSpeed() const { return d_speed; }
    void setSpeed(const Vector2F& i_speed) { d_speed = i_speed; }

    const Vector2F& getAccel() const { return d_accel; }
    void setAccel(const Vector2F& i_accel) { d_accel = i_accel; }

    bool update(float i_dt);

  protected:

    Vector2F d_speed;
    Vector2F d_accel;

    virtual bool beforeUpdate(float i_dt) { return true; }
    virtual bool afterUpdate(float i_dt) { return true; }

  };

} // ns Doh3d
