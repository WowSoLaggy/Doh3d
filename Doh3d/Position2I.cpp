#include "PrecompiledHeader.h"
#include "Position2I.h"


namespace Doh3d
{

  D3DXVECTOR3 toD3DXVECTOR3(const Position2I& i_position2i)
  {
    return D3DXVECTOR3((FLOAT)i_position2i.x, (FLOAT)i_position2i.y, 0);
  }

} // ns Doh3d
