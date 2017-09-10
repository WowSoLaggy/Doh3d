#pragma once

#include "IShape.h"
#include "Vector2I.h"
#include "Size2I.h"


namespace Doh3d
{

class RectI : public IShape
{
public:

  RectI();
  RectI(int pLeft, int pTop, int pRight, int pBottom);
  RectI(const Vector2I& pPosition, const Size2I& pSize);
  virtual ~RectI() { }


  virtual bool containsPoint(const Vector2I& pPoint) const override;
  virtual bool containsPoint(const Vector2F& pPoint) const override;

  bool containsRect(const RectI& pRect) const;

public:

  int d_left;
  int d_top;
  int d_right;
  int d_bottom;

  RectI operator + (const Vector2I& pOffset) const;
  RectI operator - (const Vector2I& pOffset) const;

};

} // ns Doh3d
