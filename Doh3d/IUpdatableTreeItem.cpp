#include "Doh3d.h"
#include "IUpdatableTreeItem.h"


namespace Doh3d
{

  bool IUpdatable::updateTree(float pDt)
  {
    if (!updateSelf(pDt))
      return false;

    for (auto child : d_children)
    {
      if (auto* pUpdatableChild = dynamic_cast<IUpdatable*>(child))
      {
        if (!pUpdatableChild->updateTree(pDt))
          return false;
      }
    }

    return true;
  }

} // ns Doh3d
