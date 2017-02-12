#include "PrecompiledHeader.h"
#include "IUpdatableTreeItem.h"


namespace Doh3d
{

  bool IUpdatableTreeItem::update(float pDt)
  {
    return updateTree(pDt);
  }


  bool IUpdatableTreeItem::updateTree(float pDt)
  {
    if (isDeleted())
      return true;

    if (!updateSelf(pDt))
      return false;

    for (int i = 0; i < (int)d_children.size();)
    {
      if (auto* pUpdatableChild = dynamic_cast<IUpdatableTreeItem*>(d_children[i]))
      {
        if (isDeleted())
          return true;

        if (!pUpdatableChild->updateTree(pDt))
          return false;

        if (pUpdatableChild->isDeleted())
          removeChild(pUpdatableChild);
        else
          ++i;
      }
    }

    return true;
  }

} // ns Doh3d
