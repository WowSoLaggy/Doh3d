#pragma once

#ifndef INC_DOH3D_ITREEITEM_H
#define INC_DOH3D_ITREEITEM_H


namespace Doh3d
{

  class ITreeItem
  {
  public:

    ITreeItem();
    virtual ~ITreeItem();


    ITreeItem* parent() { return d_parent; }
    const ITreeItem* parent() const { return d_parent; }

    std::vector<ITreeItem*>& children() { return d_children; }
    const std::vector<ITreeItem*>& children() const { return d_children; }


    void addChild(ITreeItem* pChild);
    void removeChild(ITreeItem* pChild);

  protected:

    ITreeItem* d_parent;
    std::vector<ITreeItem*> d_children;

  };

} // ns Doh3d


#endif // INC_DOH3D_ITREEITEM_H
