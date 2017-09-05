#pragma once


namespace Doh3d
{

  class ITextured
  {
  public:

    virtual ~ITextured() { }

    virtual bool loadAllTextures() PURE;

  };

} // ns Doh3d
