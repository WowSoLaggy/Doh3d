#pragma once


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

    std::vector<ITreeItem*> rchildren() { return std::vector<ITreeItem*>(d_children.rbegin(), d_children.rend()); }


    void addChildBack(ITreeItem* pChild);
    void addChildFront(ITreeItem* pChild);
    void removeChild(ITreeItem* pChild);

    bool isDeleted() { return d_deleted; }
    void deleteThis();

  protected:

    bool d_deleted;

    ITreeItem* d_parent;
    std::vector<ITreeItem*> d_children;

  };


  template<typename T>
  T* findChildByType(const ITreeItem& pRoot, int pDepth = -1)
  {
    if (pDepth == 0)
      return nullptr;
    --pDepth;

    for (auto* pChild : pRoot.children())
    {
      if (!pChild)
        continue;

      if (auto* pT = dynamic_cast<T*>(pChild))
        return pT;

      if (auto* pT = findChildByType<T>(*pChild, pDepth))
        return pT;
    }

    return nullptr;
  }

} // ns Doh3d
