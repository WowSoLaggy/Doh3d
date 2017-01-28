#include "Doh3d.h"
#include "IDrawableTreeItem.h"


namespace Doh3d
{

  bool IDrawable::drawTree(int x) const
  {
    if (!drawSelf(x))
      return false;

    for (auto child : d_children)
    {
      if (auto* pDrawableChild = dynamic_cast<IDrawable*>(child))
      {
        if (!pDrawableChild->drawTree(x))
          return false;
      }
    }

    return true;
  }

} // ns Doh3d
