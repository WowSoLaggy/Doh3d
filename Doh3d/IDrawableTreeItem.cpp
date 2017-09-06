#include "PrecompiledHeader.h"
#include "IDrawableTreeItem.h"


namespace Doh3d
{

  bool IDrawableTreeItem::draw(Sprite& pSprite) const
  {
    return drawTree(pSprite);
  }


  bool IDrawableTreeItem::drawTree(Sprite& pSprite) const
  {
    if (!drawSelf(pSprite))
      return false;

    if (!drawChildren())
      return true;

    for (int i = 0; i < (int)d_children.size(); ++i)
    {
      if (auto* pDrawableChild = dynamic_cast<IDrawableTreeItem*>(d_children[i]))
      {
        if (!pDrawableChild->drawTree(pSprite))
          return false;
      }
    }

    return true;
  }

} // ns Doh3d
