#pragma once

#ifndef INC_DOH3D_MATRIX_H
#define INC_DOH3D_MATRIX_H


namespace Doh3d
{

  class Matrix : public D3DXMATRIX
  {
  public:

    static Matrix Identity();

  };

} // ns Doh3d


#endif // INC_DOH3D_MATRIX_H
