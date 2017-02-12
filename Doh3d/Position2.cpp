#include "PrecompiledHeader.h"
#include "Position2.h"


namespace Doh3d
{

  Position2::Position2()
    : Position2(0, 0)
  {
  }

  Position2::Position2(int pX, int pY)
    : d_rawVector(D3DXVECTOR3((FLOAT)pX, (FLOAT)pY, 0))
  {
  }

  Position2::Position2(float pX, float pY)
    : Position2((int)pX, (int)pY)
  {
  }

  Position2::Position2(const D3DXVECTOR2& pVector2)
    : Position2((int)pVector2.x, (int)pVector2.y)
  {
  }

  Position2::Position2(const D3DXVECTOR3& pVector3)
    : Position2((int)pVector3.x, (int)pVector3.y)
  {
  }



  Position2 Position2::operator+(const Position2& pPosition) const
  {
    return Position2(d_rawVector.x + pPosition.d_rawVector.x, d_rawVector.y + pPosition.d_rawVector.y);
  }

  Position2 Position2::operator-(const Position2& pPosition) const
  {
    return Position2(d_rawVector.x - pPosition.d_rawVector.x, d_rawVector.y - pPosition.d_rawVector.y);
  }


  Position2 Position2::operator+(const Size2& pSize) const
  {
    return Position2(d_rawVector.x + pSize.x(), d_rawVector.y + pSize.y());
  }

  Position2 Position2::operator-(const Size2& pSize) const
  {
    return Position2(d_rawVector.x - pSize.x(), d_rawVector.y - pSize.y());
  }

} // ns Doh3d
