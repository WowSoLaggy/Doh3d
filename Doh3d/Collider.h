#pragma once

#include "IShape.h"
#include "RectF.h"
#include "Circle.h"


namespace Doh3d
{

class Collider
{
public:

  static bool collide(
    const IShape& i_shape1, const IShape& i_shape2,
    const Vector2F& i_offset1 = { 0, 0 }, const Vector2F& i_offset2 = { 0, 0 });

  static bool collideRectToCircle(
    const RectF& i_rect, const Circle& i_circle,
    const Vector2F& i_offsetRect = { 0, 0 }, const Vector2F& i_offsetCircle = { 0, 0 });

private:

  Collider();

};

} // ns Doh3d
