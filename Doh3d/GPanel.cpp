#include "Doh3d.h"
#include "GPanel.h"

#include "ResourceMan.h"


namespace Doh3d
{

	GPanel::GPanel(float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName)
	{
		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;
		m_size.x = pSizeX;
		m_size.y = pSizeY;

		m_textureName = pTextureName;

		m_tiMain = 0;
	}

	GPanel::~GPanel()
	{
	}


	ErrCode3d GPanel::Load()
	{
		LOG("GPanel::Load()");
		ErrCode3d err;

		err = ResourceMan::GetTi(m_textureName, m_tiMain);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get TI for panel (id: ", m_id, ").");
			return err;
		}

		err = UpdateTransformMatrix();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't update TransformMatrix for button (id: ", m_id, ").");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d GPanel::Unload()
	{
		return err3d_noErr;
	}

	ErrCode3d GPanel::Draw(Sprite& pSprite) const
	{
		LOG("GPanel::Draw()");
		int hRes;

		pSprite.Get()->SetTransform(&m_transformMatrix);

		hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiMain).Get(), 0, 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw sprite.");
			return err3d_cantDrawSprite;
		}

		return err3d_noErr;
	}

	D3DXVECTOR2 GPanel::GetOriginalSize() const
	{
		return ResourceMan::GetTexture(m_tiMain).GetSize();
	}


	ErrCode3d GPanel::OnMouseMove(bool &pHandled)
	{
		pHandled = false;
		return err3d_noErr;
	}

	ErrCode3d GPanel::OnMouseDown(bool &pHandled, int pButton)
	{
		pHandled = false;
		return err3d_noErr;
	}

	ErrCode3d GPanel::OnMouseUp(bool &pHandled, int pButton)
	{
		pHandled = false;
		return err3d_noErr;
	}

} // ns Doh3d
