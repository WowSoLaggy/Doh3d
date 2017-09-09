#pragma once

#include "Position2F.h"


namespace Doh3d
{

class IPositioned2F
{
public:

  virtual ~IPositioned2F() { }

  virtual const Position2F& getPosition() const { return d_position; }
  virtual void setPosition(const Position2F& pPosition) { d_position = pPosition; }

protected:

  Position2F d_position;

};

} // ns Doh3d
