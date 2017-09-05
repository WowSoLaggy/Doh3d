#pragma once

#include "ITreeItem.h"


namespace Doh3d
{

  class IDrawableTreeItem : public virtual ITreeItem
  {
  public:

    virtual ~IDrawableTreeItem() { }

    bool draw(Sprite& pSprite) const;

  private:

    bool drawTree(Sprite& pSprite) const;
    virtual bool drawSelf(Sprite& pSprite) const PURE;

  };

} // ns Doh3d
