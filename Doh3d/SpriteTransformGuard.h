#pragma once


namespace Doh3d
{

class Sprite;


class SpriteTransformGuard
{
public:

  SpriteTransformGuard(Sprite& i_sprite);
  ~SpriteTransformGuard();

private:

  Sprite& d_sprite;

  Position2I d_spriteTranslation;
  Vector2F d_spriteScale;
};

} // ns Doh3d
