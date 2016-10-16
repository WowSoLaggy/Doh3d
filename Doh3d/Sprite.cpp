#include "Doh3d.h"
#include "Sprite.h"


namespace Doh3d
{

	ErrCode3d Sprite::Begin()
	{
		LOG("Sprite::Begin()");
		HRESULT hRes;

		hRes = m_sprite->Begin(0);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't begin sprite.");
			return err3d_cantBeginSprite;
		}

		return err3d_noErr;
	}

	ErrCode3d Sprite::End()
	{
		LOG("Sprite::End()");
		HRESULT hRes;

		hRes = m_sprite->End();
		if (hRes != S_OK)
		{
			echo("ERROR: Can't end sprite.");
			return err3d_cantEndSprite;
		}

		return err3d_noErr;
	}


	ErrCode3d Sprite::Load()
	{
		LOG("Sprite::Load()");
		HRESULT hRes;

		hRes = D3DXCreateSprite(RenderMan::GetRenderDevice(), &m_sprite);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create sprite.");
			return err3d_cantCreateSprite;
		}

		return err3d_noErr;
	}

	ErrCode3d Sprite::Unload()
	{
		if (m_sprite != nullptr)
		{
			m_sprite->Release();
			m_sprite = nullptr;
		}

		return err3d_noErr;
	}

	ErrCode3d Sprite::Reload()
	{
		LOG("Sprite::Reload()");
		ErrCode3d err3d;

		err3d = Unload();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't unload sprite.");
			return err3d;
		}

		err3d = Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load sprite.");
			return err3d;
		}

		return err3d_noErr;
	}

} // Doh3d
