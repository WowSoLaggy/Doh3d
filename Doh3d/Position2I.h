#pragma once

#include "Vector2I.h"


namespace Doh3d
{

  using Position2I = Vector2I;

  D3DXVECTOR3 toD3DXVECTOR3(const Position2I& i_position2i);

} // ns Doh3d
