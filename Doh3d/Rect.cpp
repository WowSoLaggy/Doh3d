#include "PrecompiledHeader.h"
#include "Rect.h"


namespace Doh3d
{
	namespace Geometry
	{

    RectI::RectI()
			: RectI(0, 0, 0, 0)
		{
		}

    RectI::RectI(int pLeft, int pTop, int pRight, int pBottom)
			: d_left(pLeft), d_top(pTop), d_right(pRight), d_bottom(pBottom)
		{
		}

    RectI::RectI(const Position2& pPosition, const Size2& pSize)
      : d_left(pPosition.x()), d_top(pPosition.y()), d_right(pPosition.x() + pSize.x()), d_bottom(pPosition.y() + pSize.y())
    {
    }


    RectI RectI::operator + (const Position2& pOffset) const
		{
			return RectI(d_left + pOffset.x(), d_top + pOffset.y(), d_right + pOffset.x(), d_bottom + pOffset.y());
		}

    RectI RectI::operator - (const Position2& pOffset) const
		{
			return RectI(d_left - pOffset.x(), d_top - pOffset.y(), d_right - pOffset.x(), d_bottom - pOffset.y());
		}


		bool RectI::containsPoint(int pX, int pY) const
		{
			return !((pX < d_left) || (d_right < pX) || (pY < d_top) || (d_bottom < pY));
		}

		bool RectI::containsPoint(const Position2& pPoint) const
		{
			return containsPoint(pPoint.x(), pPoint.y());
		}


		bool RectI::containsRect(const RectI& pRect) const
		{
			return d_left <= pRect.d_left && pRect.d_right <= d_right && d_top <= pRect.d_top && pRect.d_bottom <= d_bottom;
		}

	} // ns Geometry
} // Doh3d
