#include "Doh3d.h"
#include "Cursor.h"


namespace Doh3d
{

	int Cursor::m_ti;
	D3DXMATRIX Cursor::m_identityMatrix = Matrix::Identity();


	ErrCode3d Cursor::SetCursorTexture(const std::string& pTextureName)
	{
		LOG("Cursor::SetCursorTexture()");
		ErrCode3d err3d;

		err3d = ResourceMan::GetTi(pTextureName, m_ti);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't find cursor's texture to set.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d Cursor::Draw(const Sprite& pSprite)
	{
		LOG("Cursor::Draw()");
		HRESULT hRes;

		if (m_ti == -1)
		{
			echo("ERROR: Can't draw cursor: cursor texture is not set.");
			return err3d_cantCursorTextureIsNotSet;
		}

		D3DXVECTOR2 pos = InputMan::GetCursorPosition();
		
		pSprite.Get()->SetTransform(&m_identityMatrix);
		hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_ti).Get(), &ResourceMan::GetTexture(m_ti).GetFrame(0), 0, &D3DXVECTOR3(pos.x, pos.y, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw cursor.");
			return err3d_cantDrawSprite;
		}

		return err3d_noErr;
	}

} // ns Doh3d
