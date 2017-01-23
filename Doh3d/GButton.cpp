#include "Doh3d.h"
#include "GButton.h"

#include "ResourceMan.h"


namespace Doh3d
{

	GButton::GButton(float pPosX, float pPosY, float pSizeX, float pSizeY,
					 const std::string& pTexNameNormal, const std::string& pTexNamePressed,
					 const std::string& pTexNameSelected, const std::string& pTexNameDisabled)
	{
		LOG("GButton::GButton()");

		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;

		if (!SetSize(pSizeX, pSizeY))
			echo("ERROR: Can't set size.");

		m_texNameNormal = pTexNameNormal;
		m_texNamePressed = pTexNamePressed;
		m_texNameSelected = pTexNameSelected;
		m_texNameDisabled = pTexNameDisabled;

		m_tiNormal = 0;
		m_tiPressed = 0;
		m_tiSelected = 0;
		m_tiDisabled = 0;

		m_state = GStates::Normal;

		OnClickEvent = nullptr;

		m_textContainer.SetTextAlign(TextAlign::Center);
	}

	GButton::~GButton()
	{
	}


  bool GButton::Load()
	{
		LOG("GButton::Load()");

		if (!ResourceMan::GetTi(m_texNameNormal, m_tiNormal))
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNameNormal, "\".");
			return false;
		}

		if (!ResourceMan::GetTi(m_texNamePressed, m_tiPressed))
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNamePressed, "\".");
			return false;
		}

		if (!ResourceMan::GetTi(m_texNameSelected, m_tiSelected))
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNameSelected, "\".");
			return false;
		}

		if (!ResourceMan::GetTi(m_texNameDisabled, m_tiDisabled))
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNameDisabled, "\".");
			return false;
		}

		if (!UpdateTransformMatrix())
		{
			echo("ERROR: Can't update TransformMatrix for GButton (id: ", m_id, ").");
			return false;
		}

		if (!m_textContainer.Load())
		{
			echo("ERROR: Can't load TextContainer for GButton (id: ", m_id, ").");
			return false;
		}

		if (!m_textContainer.SetBasisPosition(D3DXVECTOR3(GetSize().x / 2, GetSize().y / 2, 0)))
		{
			echo("ERROR: Can't set basis for TextContainer.");
			return false;
		}

		return true;
	}

  bool GButton::Unload()
	{
		LOG("GButton::Unload()");

		if (!m_textContainer.Unload())
		{
			echo("ERROR: Can't unload TextContainer for GButton (id: ", m_id, ").");
			return false;
		}

		return true;
	}

  bool GButton::Draw(Sprite& pSprite) const
	{
		LOG("GButton::Draw()");
		int hRes;

		pSprite.Get()->SetTransform(&m_transformMatrix);

		switch (m_state)
		{
		case GStates::Pressed:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiPressed).Get(), &ResourceMan::GetTexture(m_tiPressed).GetFrame(0), 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case GStates::Selected:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiSelected).Get(), &ResourceMan::GetTexture(m_tiSelected).GetFrame(0), 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case GStates::Disabled:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiDisabled).Get(), &ResourceMan::GetTexture(m_tiDisabled).GetFrame(0), 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		default:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiNormal).Get(), &ResourceMan::GetTexture(m_tiNormal).GetFrame(0), 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		}

		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw sprite.");
			return false;
		}

		if (m_textContainer.HasText())
		{
			hRes = pSprite.Get()->Draw(m_textContainer.GetTexture(), 0, 0, &(m_position + m_textContainer.GetPosition()), D3DCOLOR_ARGB(255, 255, 255, 255));
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw text.");
				return false;
			}
		}

		return true;
	}

	D3DXVECTOR2 GButton::GetOriginalSize() const
	{
		return ResourceMan::GetTexture(m_tiNormal).GetSize();
	}

  bool GButton::OnMouseMove(bool& pHandled)
	{
		LOG("GButton::OnMouseMove()");

		if (!GBase::OnMouseMove(pHandled))
		{
			echo("ERROR: Error occurred while GBase::OnMouseMove().");
			return false;
		}

		if (m_state == GStates::Disabled)
			return true;

		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			if (m_state == GStates::Normal)
				m_state = GStates::Selected;
		}
		else
			m_state = GStates::Normal;

		return true;
	}

  bool GButton::OnMouseDown(bool& pHandled, int pButton)
	{
		LOG("GButton::OnMouseDown()");

		if (!GBase::OnMouseDown(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::OnMouseDown().");
			return false;
		}

		if (m_state == GStates::Disabled)
			return true;

		if (pButton != MBUTTON_LEFT)
			return true;

		if (ContainsPoint(InputMan::GetCursorPosition()))
			m_state = GStates::Pressed;
		else
			m_state = GStates::Normal;

		return true;
	}

  bool GButton::OnMouseUp(bool& pHandled, int pButton)
	{
		LOG("GButton::OnMouseUp()");

		if (pButton != MBUTTON_LEFT)
		{
			pHandled = false;
			return true;
		}

		if (!GBase::OnMouseUp(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::OnMouseUp().");
			return false;
		}

		if (m_state == GStates::Disabled)
			return true;

		if (pButton != MBUTTON_LEFT)
			return true;

		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			if (m_state == GStates::Pressed)
			{
				if (!Click())
				{
					echo("ERROR: Error occurred while button click.");
					return false;
				}
			}

			m_state = GStates::Selected;
		}
		else
			m_state = GStates::Normal;

		return true;
	}

  bool GButton::SetOnClickEvent(std::function<void()> pEvent)
	{
		OnClickEvent = pEvent;
		return true;
	}

  bool GButton::Click()
	{
		LOG("GButton::Click()");
		
		if ((m_state == GStates::Disabled) || (!m_isVisible))
			return true;

		if (OnClickEvent != nullptr)
			OnClickEvent();

		return true;
	}


  bool GButton::SetText(const std::string& pText)
	{
		LOG("GButton::SetText()");

		if (!m_textContainer.SetText(pText))
		{
			echo("ERROR: Can't set text to TextContainer.");
			return false;
		}

		return true;
	}

  bool GButton::SetFont(const std::string& pFontName)
	{
		LOG("GButton::SetFont()");

		if (!m_textContainer.SetFont(pFontName))
		{
			echo("ERROR: Can't set font for GButton (id: ", m_id, ").");
			return false;
		}

		return true;
	}

} // ns Doh3d
