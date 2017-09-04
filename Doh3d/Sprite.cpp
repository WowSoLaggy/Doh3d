#include "PrecompiledHeader.h"
#include "Sprite.h"


namespace Doh3d
{

  Sprite::Sprite()
    : d_sprite(nullptr)
  {
    d_translation = Position2I::zero();
    d_scale = Vector2F::identity();
  }


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


  bool Sprite::draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT *pSrcRect, CONST D3DXVECTOR3 *pCenter, const Position2I& pPosition, D3DCOLOR Color)
  {
    LOG(__FUNCTION__);

    if (d_sprite->Draw(pTexture, pSrcRect, pCenter, &toD3DXVECTOR3(pPosition), Color) != S_OK)
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

    updateTransform();

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


  void Sprite::setTranslation(const Position2I& i_translation)
  {
    d_translation = i_translation;
    updateTransform();
  }

  void Sprite::setScale(const Vector2F& i_scale)
  {
    d_scale = i_scale;
    updateTransform();
  }


  void Sprite::updateTransform()
  {
    D3DXMATRIX translationMatrix;
    D3DXMatrixTranslation(&translationMatrix, (FLOAT)d_translation.x, (FLOAT)d_translation.y, 0);

    D3DXMATRIX scaleMatrix;
    D3DXVECTOR2 scaleCenter(0, 0);
    D3DXVECTOR2 scale((FLOAT)d_scale.x, (FLOAT)d_scale.y);
    D3DXMatrixTransformation2D(&scaleMatrix, &scaleCenter, 0, &scale, 0, 0, 0);

    D3DXMATRIX finalTransform;
    D3DXMatrixMultiply(&finalTransform, &translationMatrix, &scaleMatrix);

    d_sprite->SetTransform(&finalTransform);
  }

} // Doh3d
