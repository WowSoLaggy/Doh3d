#include "Doh3d.h"
#include "IVisiter.h"


namespace Doh3d
{

  bool IVisiter::visit(ITreeItem& pTreeItem)
  {
    return true;
  }

  bool IVisiter::visit(const ITreeItem& pTreeItem) const
  {
    return true;
  }

} // ns Doh3d
