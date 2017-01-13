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
			: Left(pLeft), Top(pTop), Right(pRight), Bottom(pBottom)
		{
		}


		Rect Rect::operator + (const D3DXVECTOR2& pOffset) const
		{
			return Rect(Left + pOffset.x, Top + pOffset.y, Right + pOffset.x, Bottom + pOffset.y);
		}

		Rect Rect::operator - (const D3DXVECTOR2& pOffset) const
		{
			return Rect(Left - pOffset.x, Top - pOffset.y, Right - pOffset.x, Bottom - pOffset.y);
		}


		bool Rect::ContainsPoint(float pX, float pY) const
		{
			return !((pX < Left) || (Right < pX) || (pY < Top) || (Bottom < pY));
		}

		bool Rect::ContainsPoint(const D3DXVECTOR2& pPoint) const
		{
			return ContainsPoint(pPoint.x, pPoint.y);
		}


		bool Rect::ContainsRect(const Rect& pRect) const
		{
			return Left <= pRect.Left && pRect.Right <= Right && Top <= pRect.Top && pRect.Bottom <= Bottom;
		}

	} // ns Geometry
} // Doh3d
