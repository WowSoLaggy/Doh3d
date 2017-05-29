#include "PrecompiledHeader.h"
#include "Texture.h"


namespace Doh3d
{

  bool Texture::reload()
  {
    return load(true);
  }

  bool Texture::load()
  {
    return load(false);
  }

  bool Texture::unload()
  {
    if (d_texture != nullptr)
    {
      d_texture->Release();
      d_texture = nullptr;
    }

    return true;
  }

  bool Texture::load(bool pForceReload)
  {
    LOG("RTexture::load()");
    HRESULT hRes;

    if (d_texture != nullptr && !pForceReload)
      return true;

    std::string strTemp = ResourceMan::getTextureDir();

    hRes = D3DXCreateTextureFromFileEx(RenderMan::getRenderDevice(), strTemp.append("\\").append(d_filePath).c_str(),
                                       D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &d_texture);
    if (hRes != S_OK || !d_texture)
    {
      echo("ERROR: Can't create texture from file: \"", d_filePath, "\".");
      return false;
    }

    if ((d_size.x == 0) && (d_size.y == 0))
    {
      D3DSURFACE_DESC surfaceDesc;
      d_texture->GetLevelDesc(0, &surfaceDesc);
      d_size = D3DXVECTOR2((float)surfaceDesc.Width, (float)surfaceDesc.Height);
      d_size2 = d_size / 2;
    }

    d_alphaMap.init(d_alphaCheck, d_texture);

    return true;
  }


  bool Texture::hitTest(int pX, int pY, int pFrame) const
  {
    if (pX < 0 || pY < 0 || pX >= d_size.x || pY >= d_size.y)
      return false;

    return d_alphaMap.check(pX + pFrame * (int)d_size.x, pY);
  }

  bool Texture::hitTest(float pX, float pY, int pFrame) const
  {
    return hitTest((int)pX, (int)pY, pFrame);
  }

  bool Texture::hitTest(const D3DXVECTOR2& pCoords, int pFrame) const
  {
    return hitTest((int)pCoords.x, (int)pCoords.y, pFrame);
  }

  bool Texture::hitTest(const D3DXVECTOR3& pCoords, int pFrame) const
  {
    return hitTest((int)pCoords.x, (int)pCoords.y, pFrame);
  }

  RECT Texture::getFrame(int pFrameNumber) const
  {
    RECT rect;
    rect.left = (LONG)(d_size.x * pFrameNumber);
    rect.top = 0;
    rect.right = (LONG)(d_size.x * (pFrameNumber + 1));
    rect.bottom = (LONG)(d_size.y);
    return rect;
  }

} // ns Doh3d
