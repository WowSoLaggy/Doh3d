#include "PrecompiledHeader.h"
#include "SpriteTransformGuard.h"

#include "Sprite.h"


namespace Doh3d
{

SpriteTransformGuard::SpriteTransformGuard(Sprite& i_sprite)
  : d_sprite(i_sprite)
{
  d_spriteTranslation = d_sprite.getTranslation();
  d_spriteScale = d_sprite.getScale();
}

SpriteTransformGuard::~SpriteTransformGuard()
{
  d_sprite.setTranslation(d_spriteTranslation);
  d_sprite.setScale(d_spriteScale);
}

} // ns Doh3d
