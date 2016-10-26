#pragma once

#ifndef INC_DOH3D_HITTEST_H
#define INC_DOH3D_HITTEST_H


namespace Doh3d
{

	static bool PointContainsInRect(const D3DXVECTOR2& pPoint, float pRectLeft, float pRectTop, float pRectRight, float pRectBottom)
	{
		if ((pPoint.x < pRectLeft) || (pRectRight < pPoint.x) || (pPoint.y < pRectTop) || (pRectBottom < pPoint.y))
			return false;

		return true;
	}

} // ns Doh3d


#endif // INC_DOH3D_HITTEST_H
