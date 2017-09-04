#pragma once

#include "Position2I.h"


namespace Doh3d
{

  class IPositioned2I
  {
  public:

    virtual ~IPositioned2I() { }

    virtual const Position2I getPosition() const { return d_position; }
    virtual void setPosition(const Position2I& pPosition) { d_position = pPosition; }

  protected:

    IPositioned2I() : d_position(0, 0) { }

  private:

    Position2I d_position;

  };

} // ns Doh3d
