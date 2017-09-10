#include "PrecompiledHeader.h"
#include "RectF.h"


namespace Doh3d
{

RectF::RectF()
  : RectF(0, 0, 0, 0)
{
}

RectF::RectF(float pLeft, float pTop, float pRight, float pBottom)
  : d_left(pLeft), d_top(pTop), d_right(pRight), d_bottom(pBottom)
{
}

RectF::RectF(const Vector2F& pPosition, const Size2F& pSize)
  : d_left(pPosition.x), d_top(pPosition.y), d_right(pPosition.x + pSize.x), d_bottom(pPosition.y + pSize.y)
{
}


RectF RectF::operator + (const Vector2F& pOffset) const
{
  return RectF(d_left + pOffset.x, d_top + pOffset.y, d_right + pOffset.x, d_bottom + pOffset.y);
}

RectF RectF::operator - (const Vector2F& pOffset) const
{
  return RectF(d_left - pOffset.x, d_top - pOffset.y, d_right - pOffset.x, d_bottom - pOffset.y);
}


bool RectF::containsPoint(const Vector2I& pPoint) const
{
  return !((pPoint.x < d_left) || (d_right < pPoint.x) || (pPoint.y < d_top) || (d_bottom < pPoint.y));
}

bool RectF::containsPoint(const Vector2F& pPoint) const
{
  return !((pPoint.x < d_left) || (d_right < pPoint.x) || (pPoint.y < d_top) || (d_bottom < pPoint.y));
}


bool RectF::containsRect(const RectF& pRect) const
{
  return d_left <= pRect.d_left && pRect.d_right <= d_right && d_top <= pRect.d_top && pRect.d_bottom <= d_bottom;
}

} // Doh3d
