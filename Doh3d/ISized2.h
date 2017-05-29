#pragma once

#ifndef INC_DOH3D_ISIZED2_H
#define INC_DOH3D_ISIZED2_H


#include "Size2.h"


namespace Doh3d
{

  class ISized2
  {
  public:

    virtual ~ISized2() { }

    virtual const Size2& getSize() const { return d_size; }
    virtual const Size2& getSizeHalf() const { return d_sizeHalf; }
    virtual void setSize(const Size2& pSize) { d_size = pSize; d_sizeHalf = pSize / 2; }

  protected:

    ISized2() : d_size(0, 0), d_sizeHalf(0, 0) { }

  private:

    Size2 d_size;
    Size2 d_sizeHalf;

  };

} // ns Doh3d


#endif // INC_DOH3D_ISIZED_H
