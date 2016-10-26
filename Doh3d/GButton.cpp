#include "Doh3d.h"
#include "GButton.h"

#include "ResourceMan.h"


namespace Doh3d
{

	GButton::GButton(float pPosX, float pPosY, float pSizeX, float pSizeY,
					 const std::string& pTexNameNormal, const std::string& pTexNamePressed,
					 const std::string& pTexNameSelected, const std::string& pTexNameDisabled)
	{
		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;
		m_size.x = pSizeX;
		m_size.y = pSizeY;

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
	}

	GButton::~GButton()
	{
	}


	ErrCode3d GButton::Load()
	{
		LOG("GButton::Load()");
		ErrCode3d err;

		err = ResourceMan::GetTi(m_texNameNormal, m_tiNormal);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNameNormal, "\".");
			return err;
		}

		err = ResourceMan::GetTi(m_texNamePressed, m_tiPressed);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNamePressed, "\".");
			return err;
		}

		err = ResourceMan::GetTi(m_texNameSelected, m_tiSelected);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNameSelected, "\".");
			return err;
		}

		err = ResourceMan::GetTi(m_texNameDisabled, m_tiDisabled);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get TI for GButton (id: ", m_id, "): \"", m_texNameDisabled, "\".");
			return err;
		}

		err = UpdateTransformMatrix();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't update TransformMatrix for GButton (id: ", m_id, ").");
			return err;
		}

		err = m_text.Load();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't load Text for GButton (id: ", m_id, ").");
			return err;
		}
		m_positionText.x = roundf(m_position.x + (m_size.x - m_text.Width()) / 2);
		m_positionText.y = roundf(m_position.y + (m_size.y - m_text.Height()) / 2);

		return err3d_noErr;
	}

	ErrCode3d GButton::Unload()
	{
		LOG("GButton::Unload()");
		ErrCode3d err;

		err = m_text.Unload();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't unload Text for GButton (id: ", m_id, ").");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d GButton::Draw(Sprite& pSprite) const
	{
		LOG("GButton::Draw()");
		int hRes;

		pSprite.Get()->SetTransform(&m_transformMatrix);

		switch (m_state)
		{
		case GStates::Pressed:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiPressed).Get(), 0, 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case GStates::Selected:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiSelected).Get(), 0, 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case GStates::Disabled:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiDisabled).Get(), 0, 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		default:
			hRes = pSprite.Get()->Draw(ResourceMan::GetTexture(m_tiNormal).Get(), 0, 0, &m_position, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		}

		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw sprite.");
			return err3d_cantDrawSprite;
		}

		if (m_text.IsText())
		{
			hRes = pSprite.Get()->Draw(m_text.GetTexture(), 0, 0, &m_positionText, D3DCOLOR_ARGB(255, 255, 255, 255));
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw text.");
				return err3d_cantDrawText;
			}
		}

		return err3d_noErr;
	}

	D3DXVECTOR2 GButton::GetOriginalSize() const
	{
		return ResourceMan::GetTexture(m_tiNormal).GetSize();
	}

	ErrCode3d GButton::OnMouseMove(bool& pHandled)
	{
		LOG("GButton::OnMouseMove()");
		ErrCode3d err;

		err = GBase::OnMouseMove(pHandled);
		if (err != err3d_noErr)
		{
			echo("ERROR: Error occurred while GBase::OnMouseMove().");
			return err;
		}

		if (m_state == GStates::Disabled)
			return err3d_noErr;

		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			if (m_state == GStates::Normal)
				m_state = GStates::Selected;
		}
		else
			m_state = GStates::Normal;

		return err3d_noErr;
	}

	ErrCode3d GButton::OnMouseDown(bool& pHandled, int pButton)
	{
		LOG("GButton::OnMouseDown()");
		ErrCode3d err;

		err = GBase::OnMouseDown(pHandled, pButton);
		if (err != err3d_noErr)
		{
			echo("ERROR: Error occurred while GBase::OnMouseDown().");
			return err;
		}

		if (m_state == GStates::Disabled)
			return err3d_noErr;

		if (pButton != MBUTTON_LEFT)
			return err3d_noErr;

		if (ContainsPoint(InputMan::GetCursorPosition()))
			m_state = GStates::Pressed;
		else
			m_state = GStates::Normal;

		return err3d_noErr;
	}

	ErrCode3d GButton::OnMouseUp(bool& pHandled, int pButton)
	{
		LOG("GButton::OnMouseUp()");
		ErrCode3d err;

		if (pButton != MBUTTON_LEFT)
		{
			pHandled = false;
			return err3d_noErr;
		}

		err = GBase::OnMouseUp(pHandled, pButton);
		if (err != err3d_noErr)
		{
			echo("ERROR: Error occurred while GBase::OnMouseUp().");
			return err;
		}

		if (m_state == GStates::Disabled)
			return err3d_noErr;

		if (pButton != MBUTTON_LEFT)
			return err3d_noErr;

		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			if (m_state == GStates::Pressed)
			{
				err = Click();
				if (err != err3d_noErr)
				{
					echo("ERROR: Error occurred while button click.");
					return err;
				}
			}

			m_state = GStates::Selected;
		}
		else
			m_state = GStates::Normal;

		return err3d_noErr;
	}

	ErrCode3d GButton::SetOnClickEvent(std::function<void()> pEvent)
	{
		OnClickEvent = pEvent;
		return err3d_noErr;
	}

	ErrCode3d GButton::Click()
	{
		LOG("GButton::Click()");
		
		if ((m_state == GStates::Disabled) || (!m_isVisible))
			return err3d_noErr;

		if (OnClickEvent != nullptr)
			OnClickEvent();

		return err3d_noErr;
	}


	ErrCode3d GButton::SetText(const std::string& pText)
	{
		LOG("GButton::SetText()");
		ErrCode3d err3d;

		err3d = m_text.SetText(pText);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set text.");
			return err3d;
		}

		m_positionText.x = roundf(m_position.x + (m_size.x - m_text.Width()) / 2);
		m_positionText.y = roundf(m_position.y + (m_size.y - m_text.Height()) / 2);

		return err3d_noErr;
	}

	ErrCode3d GButton::SetFont(const std::string& pFontName)
	{
		return m_text.SetFont(pFontName);
	}

} // ns Doh3d
