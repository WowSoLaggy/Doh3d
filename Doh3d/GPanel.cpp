#include "Doh3d.h"
#include "GPanel.h"

#include "ResourceMan.h"


namespace Doh3d
{

	GPanel::GPanel(float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName)
	{
		LOG("GPanel::GPanel()");

		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;
		
		if (!SetSize(pSizeX, pSizeY))
			echo("ERROR: Can't set size.");

		m_textureName = pTextureName;

		m_tiMain = 0;
	}

	GPanel::~GPanel()
	{
	}


  bool GPanel::Load()
	{
		LOG("GPanel::Load()");

		if (!ResourceMan::GetTi(m_textureName, m_tiMain))
		{
			echo("ERROR: Can't get TI for panel (id: ", m_id, ").");
			return false;
		}

		if (!UpdateTransformMatrix())
		{
			echo("ERROR: Can't update TransformMatrix for button (id: ", m_id, ").");
			return false;
		}

		return true;
	}

  bool GPanel::Unload()
	{
		return true;
	}

  bool GPanel::Draw(Sprite& pSprite) const
	{
		LOG("GPanel::Draw()");
		int hRes;

		pSprite.Get()->SetTransform(&m_transformMatrix);

		hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiMain).Get(), &ResourceMan::GetTexture(m_tiMain).GetFrame(0), 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw sprite.");
			return false;
		}

		return true;
	}

	D3DXVECTOR2 GPanel::GetOriginalSize() const
	{
		return ResourceMan::GetTexture(m_tiMain).GetSize();
	}


  bool GPanel::OnMouseMove(bool &pHandled)
	{
		LOG("GPanel::OnMouseMove()");

		if (!GBase::OnMouseMove(pHandled))
		{
			echo("ERROR: Error occurred while GBase::OnMouseMove().");
			return false;
		}

		return true;
	}

  bool GPanel::OnMouseDown(bool &pHandled, int pButton)
	{
		LOG("GPanel::OnMouseDown()");

		if (!GBase::OnMouseDown(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::OnMouseDown().");
			return false;
		}

		return true;
	}

  bool GPanel::OnMouseUp(bool &pHandled, int pButton)
	{
		LOG("GPanel::OnMouseUp()");

		if (!GBase::OnMouseUp(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::OnMouseUp().");
			return false;
		}

		return true;
	}

} // ns Doh3d
