#pragma once

#include "Size2I.h"


namespace Doh3d
{

  class ISized2I
  {
  public:

    virtual ~ISized2I() { }

    virtual const Size2I& getSize() const { return d_size; }
    virtual const Size2I& getSizeHalf() const { return d_sizeHalf; }
    virtual void setSize(const Size2I& pSize) { d_size = pSize; d_sizeHalf = pSize / 2; }

  protected:

    ISized2I() : d_size(0, 0), d_sizeHalf(0, 0) { }

  private:

    Size2I d_size;
    Size2I d_sizeHalf;

  };

} // ns Doh3d
