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
    for (auto child : d_childs)
      delete child;
  }


  bool ITreeItem::traverseTree(IVisiter& pVisiter)
  {
    if (!pVisiter.visit(*this))
      return false;

    for (auto child : d_childs)
    {
      if (!pVisiter.visit(*child))
        return false;
    }

    return true;
  }

  bool ITreeItem::traverseTree(const IVisiter& pVisiter) const
  {
    if (!pVisiter.visit(*this))
      return false;

    for (auto child : d_childs)
    {
      if (!pVisiter.visit(*child))
        return false;
    }

    return true;
  }


  void ITreeItem::addChild(ITreeItem* pChild)
  {
    if (!pChild || pChild->d_parent == this)
      return;
    if (pChild->d_parent != nullptr)
      pChild->d_parent->removeChild(pChild);

    pChild->d_parent = this;
    d_childs.push_back(pChild);
  }

  void ITreeItem::removeChild(ITreeItem* pChild)
  {
    if (!pChild || pChild->d_parent != this)
      return;
    auto& it = std::find(d_childs.begin(), d_childs.end(), pChild);
    if (it == d_childs.end())
      return;

    d_childs.erase(it);
    pChild->d_parent = nullptr;
  }

} // ns Doh3d
