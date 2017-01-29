#pragma once

#ifndef INC_DOH3D_GBASE_H
#define INC_DOH3D_GBASE_H


#include "IUpdatableTreeItem.h"
#include "IDrawableTreeItem.h"


namespace Doh3d
{

  class GBase : public virtual IUpdatableTreeItem, public virtual IDrawableTreeItem
  {
  public:

    virtual ~GBase() { }

    virtual bool updateSelf(float pDt) override;
    virtual bool drawSelf(Sprite& pSprite) const override;

  };

} // ns Doh3d


#endif // NC_DOH3D_GBASE_H
