#pragma once

#ifndef INC_DOH3D_ITEXTURED_H
#define INC_DOH3D_ITEXTURED_H


namespace Doh3d
{

  class ITextured
  {
  public:

    virtual ~ITextured() { }

    virtual bool loadAllTextures() PURE;

  };

} // ns Doh3d


#endif // INC_DOH3D_ITEXTURED_H
