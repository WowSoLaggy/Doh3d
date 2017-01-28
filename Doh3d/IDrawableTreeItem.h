#pragma once

#ifndef INC_DOH3D_IDRAWABLETREEITEM_H
#define INC_DOH3D_IDRAWABLETREEITEM_H


#include "ITreeItem.h"


namespace Doh3d
{

  class IDrawable : public ITreeItem
  {
  public:

    bool drawTree(int x) const;

    virtual bool drawSelf(int x) const PURE;

  };

} // ns Doh3d


#endif // INC_DOH3D_IDRAWABLETREEITEM_H
