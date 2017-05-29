#pragma once

#ifndef INC_DOH3D_TEXTURE_H
#define INC_DOH3D_TEXTURE_H


#include "AlphaMap.h"


namespace Doh3d
{

  class Texture
  {
  public:

    Texture(const std::string& pFilePath, const D3DXVECTOR2& pSize, int pTotalFrames, bool pAlphaCheck)
      : d_filePath(pFilePath), d_size(pSize), d_size2(pSize / 2), d_totalFrames(pTotalFrames), d_texture(nullptr), d_alphaCheck(pAlphaCheck) { }


    const std::string& getFilePath() const { return d_filePath; }
    LPDIRECT3DTEXTURE9 get() { return d_texture; }
    const D3DXVECTOR2& getSize() const { return d_size; }
    const D3DXVECTOR2& getSize2() const { return d_size2; }

    RECT getFrame(int pFrameNumber) const;


    bool reload();
    bool load();
    bool unload();


    bool hitTest(int pX, int pY, int pFrame) const;
    bool hitTest(float pX, float pY, int pFrame) const;
    bool hitTest(const D3DXVECTOR2& pCoords, int pFrame) const;
    bool hitTest(const D3DXVECTOR3& pCoords, int pFrame) const;

  private:

    std::string d_filePath;
    D3DXVECTOR2 d_size;
    D3DXVECTOR2 d_size2;
    int d_totalFrames;
    bool d_alphaCheck;

    AlphaMap d_alphaMap;
    LPDIRECT3DTEXTURE9 d_texture;

    bool load(bool pForceReload);

  };

} // Doh3d


#endif // INC_DOH3D_TEXTURE_H
