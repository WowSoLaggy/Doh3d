#pragma once


namespace Doh3d
{

  class Sprite;


  class IDrawable
  {
  public:

    virtual ~IDrawable() { }

    virtual bool draw(Sprite& i_sprite) const PURE;

  };

} // ns Doh3d
