#pragma once

#ifndef INC_DOH3D_IDRAWABLETREEITEM_H
#define INC_DOH3D_IDRAWABLETREEITEM_H


#include "ITreeItem.h"


namespace Doh3d
{

  class IDrawableTreeItem : public virtual ITreeItem
  {
  public:

    virtual ~IDrawableTreeItem() { }

    bool drawTree(Sprite& pSprite) const;

    virtual bool drawSelf(Sprite& pSprite) const PURE;

  };

} // ns Doh3d


#endif // INC_DOH3D_IDRAWABLETREEITEM_H
