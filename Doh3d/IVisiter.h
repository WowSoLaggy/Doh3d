#pragma once

#ifndef INC_DOH3D_IVISITER_H
#define INC_DOH3D_IVISITER_H


namespace Doh3d
{

  // Alias for item to visit
  class ITreeItem;


  class IVisiter
  {
  public:

    virtual bool visit(ITreeItem& pTreeItem) { return true; }
    virtual bool visit(const ITreeItem& pTreeItem) const { return true; }

  };

} // ns Doh3d


#endif // INC_DOH3D_IVISITER_H
