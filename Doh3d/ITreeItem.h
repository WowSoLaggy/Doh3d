#pragma once

#ifndef INC_DOH3D_ITREEITEM_H
#define INC_DOH3D_ITREEITEM_H

#include "IVisiter.h"


namespace Doh3d
{

  class ITreeItem
  {
  public:

    ITreeItem();
    virtual ~ITreeItem();


    ITreeItem* parent() { return d_parent; }
    const ITreeItem* parent() const { return d_parent; }

    std::vector<ITreeItem*>& childs() { return d_childs; }
    const std::vector<ITreeItem*>& childs() const { return d_childs; }


    bool traverseTree(IVisiter& pVisiter);
    bool traverseTree(const IVisiter& pVisiter) const;

    void addChild(ITreeItem* pChild);
    void removeChild(ITreeItem* pChild);

  protected:

    ITreeItem* d_parent;
    std::vector<ITreeItem*> d_childs;

  };

} // ns Doh3d


#endif // INC_DOH3D_ITREEITEM_H
