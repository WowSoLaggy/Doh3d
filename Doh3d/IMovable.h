#pragma once

#include "Vector2F.h"


namespace Doh3d
{

  class IMovable
  {

  public:

    const Vector2F& getPosition() const { return d_position; }
    void setPosition(const Vector2F& i_position) { d_position = i_position; }

    const Vector2F& getSpeed() const { return d_speed; }
    void setSpeed(const Vector2F& i_speed) { d_speed = i_speed; }

    const Vector2F& getAccel() const { return d_accel; }
    void setAccel(const Vector2F& i_accel) { d_accel = i_accel; }

    virtual bool update(float i_dt);

  private:

    Vector2F d_position;
    Vector2F d_speed;
    Vector2F d_accel;

  };

} // ns Doh3d
