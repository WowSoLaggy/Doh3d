#include "Doh3d.h"
#include "TextContainer.h"


namespace Doh3d
{

	ErrCode3d TextContainer::Load()
	{
		LOG("TextContainer::Load()");
		ErrCode3d err3d;

		err3d = m_text.Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load text.");
			return err3d;
		}

		err3d = UpdatePosition();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't update position.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d TextContainer::Unload()
	{
		LOG("TextContainer::Unload()");
		ErrCode3d err3d;

		err3d = m_text.Unload();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't unload text.");
			return err3d;
		}

		return err3d_noErr;
	}


	ErrCode3d TextContainer::UpdatePosition()
	{
		LOG("TextContainer::UpdatePosition()");

		m_textPosition = m_textBasis;
		m_textPosition.y -= m_text.Height() / 2;

		switch (m_textAlign)
		{
		case TextAlign::Center:
		{
			m_textPosition.x -= m_text.Width() / 2;
			break;
		}
		case TextAlign::Right:
		{
			m_textPosition.x -= m_text.Width();
			break;
		}
		case TextAlign::Left:
		{
			break;
		}
		default:
		{
			echo("ERROR: Invalid TextAlign value.");
			return err3d_invalidTextAlign;
		}
		}
		
		return err3d_noErr;
	}


	ErrCode3d TextContainer::SetBasisPosition(const D3DXVECTOR3& pPosition)
	{
		LOG("TextContainer::SetBasisPosition()");
		ErrCode3d err3d;

		m_textBasis = pPosition;
		
		err3d = UpdatePosition();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't update position.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d TextContainer::SetText(const std::string& pText)
	{
		LOG("TextContainer::SetText()");
		ErrCode3d err3d;

		err3d = m_text.SetText(pText);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set text.");
			return err3d;
		}

		err3d = UpdatePosition();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't update position.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d TextContainer::SetFont(const std::string& pFontName)
	{
		LOG("TextContainer::SetFont()");
		ErrCode3d err3d;

		err3d = m_text.SetFont(pFontName);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set font.");
			return err3d;
		}

		err3d = UpdatePosition();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't update position.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d TextContainer::SetTextAlign(TextAlign pTextAlign)
	{
		LOG("TextContainer::SetTextAlign()");
		ErrCode3d err3d;

		m_textAlign = pTextAlign;

		err3d = UpdatePosition();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't update position.");
			return err3d;
		}

		return err3d_noErr;
	}

} // Doh3d
