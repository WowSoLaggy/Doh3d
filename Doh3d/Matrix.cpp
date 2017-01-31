#include "PrecompiledHeader.h"
#include "Matrix.h"


namespace Doh3d
{

  Matrix Matrix::identity()
	{
    Matrix matr;
		D3DXMatrixIdentity(&matr);
		return matr;
	}

} // ns Doh3d
