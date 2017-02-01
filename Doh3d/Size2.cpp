#include "PrecompiledHeader.h"
#include "Size2.h"


namespace Doh3d
{

  Size2::Size2()
    : Size2(0, 0)
  {
  }

  Size2::Size2(int pX, int pY)
    : d_x(pX), d_y(pY)
  {
  }

  Size2::Size2(float pX, float pY)
    : Size2((int)pX, (int)pY)
  {
  }


  Size2 Size2::operator+(const Size2& pSize) const
  {
    return Size2(d_x + pSize.d_x, d_y + pSize.d_y);
  }

  Size2 Size2::operator-(const Size2& pSize) const
  {
    return Size2(d_x - pSize.d_x, d_y - pSize.d_y);
  }

  Size2 Size2::operator/(int pRight) const
  {
    return Size2(d_x / pRight, d_y / pRight);
  }

} // ns Doh3d
