#pragma once

#ifndef INC_DOH3D_ITREEITEM_H
#define INC_DOH3D_ITREEITEM_H

#include "IVisiter.h"


namespace Doh3d
{

  class ITreeItem
  {
  public:

    ITreeItem()
    {
      d_parent = nullptr;
    }

    virtual ~ITreeItem()
    {
      for (auto child : d_childs)
        delete child;
    }


    bool traverseTree(IVisiter& pVisiter)
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


    bool traverseTree(const IVisiter& pVisiter) const
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


    virtual bool draw(Sprite& pSprite, const D3DXVECTOR3& pOffset) const
    {
      for (auto child : d_childs)
      {
        if (!child->draw(pSprite, pOffset))
          return false;
      }

      return true;
    }


    void addChild(ITreeItem* pChild)
    {
      if (!pChild || pChild->d_parent == this)
        return;
      if (pChild->d_parent != nullptr)
        pChild->d_parent->removeChild(pChild);

      pChild->d_parent = this;
      d_childs.push_back(pChild);
    }

    void removeChild(ITreeItem* pChild)
    {
      if (!pChild || pChild->d_parent != this)
        return;
      auto& it = std::find(d_childs.begin(), d_childs.end(), pChild);
      if (it == d_childs.end())
        return;

      d_childs.erase(it);
      pChild->d_parent = nullptr;
    }

    ITreeItem* parent() { return d_parent; }
    const ITreeItem* parent() const { return d_parent; }

    std::vector<ITreeItem*>& childs() { return d_childs; }
    const std::vector<ITreeItem*>& childs() const { return d_childs; }

  protected:

    ITreeItem* d_parent;
    std::vector<ITreeItem*> d_childs;
  };

} // ns Doh3d


#endif // INC_DOH3D_ITREEITEM_H
