#include "PrecompiledHeader.h"
#include "Sprite.h"


namespace Doh3d
{

  bool Sprite::begin()
	{
		LOG("Sprite::begin()");
		HRESULT hRes;

		hRes = d_sprite->Begin(0);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't begin sprite.");
			return false;
		}

		return true;
	}

  bool Sprite::end()
	{
		LOG("Sprite::end()");
		HRESULT hRes;

		hRes = d_sprite->End();
		if (hRes != S_OK)
		{
			echo("ERROR: Can't end sprite.");
			return false;
		}

		return true;
	}


  void Sprite::setTransform(const D3DXMATRIX* pTransform)
  {
    d_sprite->SetTransform(pTransform);
  }

  bool Sprite::draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT *pSrcRect, CONST D3DXVECTOR3 *pCenter, const Position2& pPosition, D3DCOLOR Color)
  {
    LOG(__FUNCTION__);

    if (d_sprite->Draw(pTexture, pSrcRect, pCenter, pPosition.rawVectorPtr(), Color) != S_OK)
    {
      echo("ERROR: Can't draw sprite.");
      return false;
    }

    return true;
  }


  bool Sprite::load()
	{
		LOG("Sprite::load()");
		HRESULT hRes;

		hRes = D3DXCreateSprite(RenderMan::getRenderDevice(), &d_sprite);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create sprite.");
			return false;
		}

		return true;
	}

  bool Sprite::unload()
	{
		if (d_sprite != nullptr)
		{
			d_sprite->Release();
			d_sprite = nullptr;
		}

		return true;
	}

  bool Sprite::reload()
	{
		LOG("Sprite::reload()");

		if (!unload())
		{
			echo("ERROR: Can't unload sprite.");
			return false;
		}

    if (!load())
		{
			echo("ERROR: Can't load sprite.");
			return false;
		}

		return true;
	}

} // Doh3d
