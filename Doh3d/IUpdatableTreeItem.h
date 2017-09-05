#pragma once

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
