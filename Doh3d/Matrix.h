#pragma once

#ifndef INC_DOH3D_MATRIX_H
#define INC_DOH3D_MATRIX_H


namespace Doh3d
{

  // Change this to be like the Position2 class, no inheritance from D3DXMATRIX
  class Matrix : public D3DXMATRIX
  {
  public:

    static Matrix identity();

  };

} // ns Doh3d


#endif // INC_DOH3D_MATRIX_H
