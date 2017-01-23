#include "Doh3d.h"
#include "Sprite.h"


namespace Doh3d
{

  bool Sprite::Begin()
	{
		LOG("Sprite::Begin()");
		HRESULT hRes;

		hRes = m_sprite->Begin(0);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't begin sprite.");
			return false;
		}

		return true;
	}

  bool Sprite::End()
	{
		LOG("Sprite::End()");
		HRESULT hRes;

		hRes = m_sprite->End();
		if (hRes != S_OK)
		{
			echo("ERROR: Can't end sprite.");
			return false;
		}

		return true;
	}


  bool Sprite::Load()
	{
		LOG("Sprite::Load()");
		HRESULT hRes;

		hRes = D3DXCreateSprite(RenderMan::GetRenderDevice(), &m_sprite);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create sprite.");
			return false;
		}

		return true;
	}

  bool Sprite::Unload()
	{
		if (m_sprite != nullptr)
		{
			m_sprite->Release();
			m_sprite = nullptr;
		}

		return true;
	}

  bool Sprite::Reload()
	{
		LOG("Sprite::Reload()");

		if (!Unload())
		{
			echo("ERROR: Can't unload sprite.");
			return false;
		}

    if (!Load())
		{
			echo("ERROR: Can't load sprite.");
			return false;
		}

		return true;
	}

} // Doh3d
