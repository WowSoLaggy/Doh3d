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
  : RectF(pPosition.x, pPosition.y, pPosition.x + pSize.x, pPosition.y + pSize.y)
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


bool RectF::containsPoint(const Vector2I& i_point) const
{
  return !((i_point.x < d_left) || (d_right < i_point.x) || (i_point.y < d_top) || (d_bottom < i_point.y));
}

bool RectF::containsPoint(const Vector2F& i_point) const
{
  return !((i_point.x < d_left) || (d_right < i_point.x) || (i_point.y < d_top) || (d_bottom < i_point.y));
}


bool RectF::containsRect(const RectF& pRect) const
{
  return d_left <= pRect.d_left && pRect.d_right <= d_right && d_top <= pRect.d_top && pRect.d_bottom <= d_bottom;
}


float RectF::getWidth() const
{
  return d_right - d_left;
}

float RectF::getHeight() const
{
  return d_bottom - d_top;
}

Vector2F RectF::getCenter() const
{
  return{ d_left + getWidth() / 2, d_top + getHeight() / 2 };
}

} // Doh3d
