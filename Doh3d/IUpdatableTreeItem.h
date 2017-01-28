#pragma once

#ifndef INC_DOH3D_IUPDATABLETREEITEM_H
#define INC_DOH3D_IUPDATABLETREEITEM_H


#include "ITreeItem.h"


namespace Doh3d
{

  class IUpdatable : public ITreeItem
  {
  public:

    bool updateTree(float pDt);

    virtual bool updateSelf(float pDt) PURE;

  };

} // ns Doh3d


#endif // INC_DOH3D_IUPDATABLETREEITEM_H
