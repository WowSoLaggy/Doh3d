#pragma once


namespace Doh3d
{

  // Change this to be like the Position2 class, no inheritance from D3DXMATRIX
  class Matrix : public D3DXMATRIX
  {
  public:

    static Matrix identity();

  };

} // ns Doh3d
