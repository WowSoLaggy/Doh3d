#include "Doh3d.h"
#include "GPanel.h"

#include "ResourceMan.h"


namespace Doh3d
{

	GPanel::GPanel(float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName)
	{
		LOG("GPanel::GPanel()");
		ErrCode3d err3d;

		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;
		
		err3d = SetSize(pSizeX, pSizeY);
		if (err3d != err3d_noErr)
			echo("ERROR: Can't set size.");

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

	const D3DXVECTOR2& GPanel::GetOriginalSize() const
	{
		return ResourceMan::GetTexture(m_tiMain).GetSize();
	}


	ErrCode3d GPanel::OnMouseMove(bool &pHandled)
	{
		LOG("GPanel::OnMouseMove()");
		ErrCode3d err;

		err = GBase::OnMouseMove(pHandled);
		if (err != err3d_noErr)
		{
			echo("ERROR: Error occurred while GBase::OnMouseMove().");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d GPanel::OnMouseDown(bool &pHandled, int pButton)
	{
		LOG("GPanel::OnMouseDown()");
		ErrCode3d err;

		err = GBase::OnMouseDown(pHandled, pButton);
		if (err != err3d_noErr)
		{
			echo("ERROR: Error occurred while GBase::OnMouseDown().");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d GPanel::OnMouseUp(bool &pHandled, int pButton)
	{
		LOG("GPanel::OnMouseUp()");
		ErrCode3d err;

		err = GBase::OnMouseUp(pHandled, pButton);
		if (err != err3d_noErr)
		{
			echo("ERROR: Error occurred while GBase::OnMouseUp().");
			return err;
		}

		return err3d_noErr;
	}

} // ns Doh3d
