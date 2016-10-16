#include "Doh3d.h"
#include "Matrix.h"


namespace Doh3d
{

	D3DXMATRIX Matrix::Identity()
	{
		D3DXMATRIX matr;
		D3DXMatrixIdentity(&matr);
		return matr;
	}

} // ns Doh3d
