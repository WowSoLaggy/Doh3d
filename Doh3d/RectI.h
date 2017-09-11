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


  int getWidth() const;
  int getHeight() const;
  Vector2I getCenter() const;

  virtual bool containsPoint(const Vector2I& i_point) const override;
  virtual bool containsPoint(const Vector2F& i_point) const override;

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
