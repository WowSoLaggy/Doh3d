#include "Doh3d.h"
#include "GText.h"


namespace Doh3d
{

	GText::GText(float pPosX, float pPosY, const std::string& pText, const std::string& pFontName)
	{
		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;
		SetSize(0, 0);
		SetText(pText);
		SetFont(pFontName);
		m_textContainer.SetTextAlign(TextAlign::Left);
	}

	GText::~GText()
	{
	}


	ErrCode3d GText::Load()
	{
		LOG("GText::Load()");
		ErrCode3d err3d;

		err3d = m_textContainer.Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load TextContainer for GText (id: ", m_id, ").");
			return err3d;
		}

		err3d = UpdateTransformMatrix();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't update TransformMatrix for GText (id: ", m_id, ").");
			return err3d;
		}

		err3d = SetSize((float)m_textContainer.TextWidth(), (float)m_textContainer.TextHeight());
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d GText::Unload()
	{
		LOG("GText::Unload()");
		ErrCode3d err;

		err = m_textContainer.Unload();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't unload TextContainer for GText (id: ", m_id, ").");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d GText::Draw(Sprite& pSprite) const
	{
		LOG("GText::Draw()");
		int hRes;

		pSprite.Get()->SetTransform(&m_transformMatrix);
		if (m_textContainer.HasText())
		{
			hRes = pSprite.Get()->Draw(m_textContainer.GetTexture(), 0, 0, &(m_position + m_textContainer.GetPosition()), D3DCOLOR_ARGB(255, 255, 255, 255));
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw Text for GText (id: ", m_id, ").");
				return err3d_cantDrawText;
			}
		}

		return err3d_noErr;
	}

	const D3DXVECTOR2& GText::GetOriginalSize() const
	{
		return GetSize();
	}

	ErrCode3d GText::SetText(const std::string& pText)
	{
		LOG("GText::SetText()");
		ErrCode3d err3d;

		err3d = m_textContainer.SetText(pText);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set text to TextContainer.");
			return err3d;
		}

		err3d = SetSize((float)m_textContainer.TextWidth(), (float)m_textContainer.TextHeight());
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d GText::SetFont(const std::string& pFontName)
	{
		LOG("GText::SetFont()");
		ErrCode3d err3d;

		err3d = m_textContainer.SetFont(pFontName);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set font for GText (id: ", m_id, ").");
			return err3d;
		}

		err3d = SetSize((float)m_textContainer.TextWidth(), (float)m_textContainer.TextHeight());
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return err3d;
		}

		return err3d_noErr;
	}


	ErrCode3d GText::SetSize(float pWidth, float pHeight)
	{
		LOG("GText::SetSize()");
		ErrCode3d err3d;

		err3d = GBase::SetSize(pWidth, pHeight);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return err3d;
		}

		err3d = m_textContainer.SetBasisPosition(D3DXVECTOR3(0, pHeight / 2, 0));
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't set basis for TextContainer.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d GText::SetSize(const D3DXVECTOR2& pSize)
	{
		return SetSize(pSize.x, pSize.y);
	}

} // ns Doh3d
