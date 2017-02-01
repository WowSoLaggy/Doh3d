#pragma once

#ifndef INC_DOH3D_ISIZED_H
#define INC_DOH3D_ISIZED_H


#include "Size2.h"


namespace Doh3d
{

  class ISized
  {
  public:

    virtual ~ISized() { }

    virtual const Size2& getSize() const { return d_size; }
    virtual const Size2& getSizeHalf() const { return d_sizeHalf; }
    virtual void setSize(const Size2& pSize) { d_size = pSize; d_sizeHalf = pSize / 2; }

  private:

    Size2 d_size;
    Size2 d_sizeHalf;

  };

} // ns Doh3d


#endif // INC_DOH3D_ISIZED_H
