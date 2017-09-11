#include "PrecompiledHeader.h"
#include "Collider.h"


namespace Doh3d
{

bool Collider::collide(
  const IShape& i_shape1, const IShape& i_shape2,
  const Vector2F& i_offset1 /* = { 0, 0 } */, const Vector2F& i_offset2 /* = { 0, 0 } */)
{
  if (auto* pShape1Rect = dynamic_cast<const RectF*>(&i_shape1))
  {
    if (auto* pShape2Rect = dynamic_cast<const RectF*>(&i_shape2))
      return false;
    else if (auto* pShape2Circle = dynamic_cast<const Circle*>(&i_shape2))
      return collideRectToCircle(*pShape1Rect, *pShape2Circle, i_offset1, i_offset2);
  }
  else if (auto* pShape1Circle = dynamic_cast<const Circle*>(&i_shape1))
  {
    if (auto* pShape2Rect = dynamic_cast<const RectF*>(&i_shape2))
      return collideRectToCircle(*pShape2Rect, *pShape1Circle, i_offset2, i_offset1);
    else if (auto* pShape2Circle = dynamic_cast<const Circle*>(&i_shape2))
      return false;
  }

  return false;
}


bool Collider::collideRectToCircle(
  const RectF& i_rect, const Circle& i_circle,
  const Vector2F& i_offsetRect /* = { 0, 0 } */, const Vector2F& i_offsetCircle /* = { 0, 0 } */)
{
  RectF rect = i_rect + i_offsetRect;
  Circle circle = i_circle + i_offsetCircle;

  Vector2F distToCircle(
    std::abs(circle.getCenter().x - rect.getCenter().x),
    std::abs(circle.getCenter().y - rect.getCenter().y));

  if (distToCircle.x > (rect.getWidth() / 2 + circle.getRadius())) { return false; }
  if (distToCircle.y > (rect.getHeight() / 2 + circle.getRadius())) { return false; }

  if (distToCircle.x <= (rect.getWidth() / 2)) { return true; }
  if (distToCircle.y <= (rect.getHeight() / 2)) { return true; }
  
  float cornerDistance_sq =
    (distToCircle.x - rect.getWidth() / 2) * (distToCircle.x - rect.getWidth() / 2) +
    (distToCircle.y - rect.getHeight() / 2) * (distToCircle.y - rect.getHeight() / 2);

  return cornerDistance_sq <= circle.getRadiusSq();
}

} // ns Doh3d
