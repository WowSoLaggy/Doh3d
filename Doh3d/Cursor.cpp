#include "PrecompiledHeader.h"
#include "Cursor.h"


namespace Doh3d
{

  int Cursor::d_ti;
  D3DXMATRIX Cursor::d_identityMatrix = Matrix::identity();


  bool Cursor::setCursorTexture(const std::string& pTextureName)
  {
    LOG("Cursor::setCursorTexture()");

    if (!ResourceMan::getTi(pTextureName, d_ti))
    {
      echo("ERROR: Can't find cursor's texture to set.");
      return false;
    }

    return true;
  }

  bool Cursor::draw(Sprite& pSprite)
  {
    LOG("Cursor::draw()");
    HRESULT hRes;

    if (d_ti == -1)
    {
      echo("ERROR: Can't draw cursor: cursor texture is not set.");
      return false;
    }

    D3DXVECTOR2 pos = InputMan::getCursorPosition();

    // TODO: restore the cursor drawing
    pSprite.setTransform(&d_identityMatrix);
    hRes = S_OK;
    //hRes = pSprite.draw(ResourceMan::getTexture(d_ti).get(), &ResourceMan::getTexture(d_ti).getFrame(0), 0, &D3DXVECTOR3(pos.x, pos.y, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
    if (hRes != S_OK)
    {
      echo("ERROR: Can't draw cursor.");
      return false;
    }

    return true;
  }

} // ns Doh3d
