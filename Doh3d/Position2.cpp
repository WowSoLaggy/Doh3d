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

} // ns Doh3d
