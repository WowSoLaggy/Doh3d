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
    if (!updateSelf(pDt))
      return false;

    for (int i = 0; i < (int)d_children.size(); ++i)
    {
      if (auto* pUpdatableChild = dynamic_cast<IUpdatableTreeItem*>(d_children[i]))
      {
        if (!pUpdatableChild->updateTree(pDt))
          return false;
      }
    }

    return true;
  }

} // ns Doh3d
