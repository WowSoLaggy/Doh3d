#pragma once

#ifndef INC_DOH3D_IPOSITIONED_H
#define INC_DOH3D_IPOSITIONED_H


#include "Position2.h"


namespace Doh3d
{

  class IPositioned
  {
  public:

    virtual ~IPositioned() { }

    virtual const Position2& getPosition() const { return d_position; }
    virtual void setPosition(const Position2& pPosition) { d_position = pPosition; }

  private:

    Position2 d_position;

  };

} // ns Doh3d


#endif // INC_DOH3D_IPOSITIONED_H