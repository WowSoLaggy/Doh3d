#pragma once

#include "IShape.h"
#include "Vector2F.h"
#include "Size2F.h"


namespace Doh3d
{

class RectF : public IShape
{
public:

  RectF();
  RectF(float pLeft, float pTop, float pRight, float pBottom);
  RectF(const Vector2F& pPosition, const Size2F& pSize);
  virtual ~RectF() { }


  float getWidth() const;
  float getHeight() const;
  Vector2F getCenter() const;

  virtual bool containsPoint(const Vector2I& i_point) const override;
  virtual bool containsPoint(const Vector2F& i_point) const override;

  bool containsRect(const RectF& pRect) const;


  RectF operator + (const Vector2F& i_offset) const;
  RectF operator - (const Vector2F& i_offset) const;

private:

  float d_left;
  float d_top;
  float d_right;
  float d_bottom;

};

} // ns Doh3d
