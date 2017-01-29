#include "Doh3d.h"
#include "ITreeItem.h"


namespace Doh3d
{

  ITreeItem::ITreeItem()
  {
    d_parent = nullptr;
  }

  ITreeItem::~ITreeItem()
  {
    for (auto child : d_children)
      delete child;
  }


  void ITreeItem::addChildBack(ITreeItem* pChild)
  {
    if (!pChild || pChild->d_parent == this)
      return;
    if (pChild->d_parent != nullptr)
      pChild->d_parent->removeChild(pChild);

    pChild->d_parent = this;
    d_children.push_back(pChild);
  }

  void ITreeItem::addChildFront(ITreeItem* pChild)
  {
    if (!pChild || pChild->d_parent == this)
      return;
    if (pChild->d_parent != nullptr)
      pChild->d_parent->removeChild(pChild);

    pChild->d_parent = this;
    d_children.insert(d_children.begin(), pChild);
  }

  void ITreeItem::removeChild(ITreeItem* pChild)
  {
    if (!pChild || pChild->d_parent != this)
      return;
    auto& it = std::find(d_children.begin(), d_children.end(), pChild);
    if (it == d_children.end())
      return;

    d_children.erase(it);
    pChild->d_parent = nullptr;
  }

} // ns Doh3d
