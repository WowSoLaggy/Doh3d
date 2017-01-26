#include "Doh3d.h"
#include "Rect.h"


namespace Doh3d
{
	namespace Geometry
	{

		Rect::Rect()
			: Rect(0, 0, 0, 0)
		{
		}

		Rect::Rect(float pLeft, float pTop, float pRight, float pBottom)
			: d_left(pLeft), d_top(pTop), d_right(pRight), d_bottom(pBottom)
		{
		}


		Rect Rect::operator + (const D3DXVECTOR2& pOffset) const
		{
			return Rect(d_left + pOffset.x, d_top + pOffset.y, d_right + pOffset.x, d_bottom + pOffset.y);
		}

		Rect Rect::operator - (const D3DXVECTOR2& pOffset) const
		{
			return Rect(d_left - pOffset.x, d_top - pOffset.y, d_right - pOffset.x, d_bottom - pOffset.y);
		}


		bool Rect::containsPoint(float pX, float pY) const
		{
			return !((pX < d_left) || (d_right < pX) || (pY < d_top) || (d_bottom < pY));
		}

		bool Rect::containsPoint(const D3DXVECTOR2& pPoint) const
		{
			return containsPoint(pPoint.x, pPoint.y);
		}


		bool Rect::containsRect(const Rect& pRect) const
		{
			return d_left <= pRect.d_left && pRect.d_right <= d_right && d_top <= pRect.d_top && pRect.d_bottom <= d_bottom;
		}

	} // ns Geometry
} // Doh3d
