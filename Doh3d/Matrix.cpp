#include "Doh3d.h"
#include "Matrix.h"


namespace Doh3d
{

  Matrix Matrix::Identity()
	{
    Matrix matr;
		D3DXMatrixIdentity(&matr);
		return matr;
	}

} // ns Doh3d
