#pragma once

#ifndef INC_DOH3D_IUPDATABLETREEITEM_H
#define INC_DOH3D_IUPDATABLETREEITEM_H


#include "ITreeItem.h"


namespace Doh3d
{

  class IUpdatableTreeItem : public virtual ITreeItem
  {
  public:

    virtual ~IUpdatableTreeItem() { }

    bool update(float pDt);

  private:

    bool updateTree(float pDt);
    virtual bool updateSelf(float pDt) PURE;

  };

} // ns Doh3d


#endif // INC_DOH3D_IUPDATABLETREEITEM_H
