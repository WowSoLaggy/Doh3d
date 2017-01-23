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


  bool GText::Load()
	{
		LOG("GText::Load()");

		if (!m_textContainer.Load())
		{
			echo("ERROR: Can't load TextContainer for GText (id: ", m_id, ").");
			return false;
		}

		if (!UpdateTransformMatrix())
		{
			echo("ERROR: Can't update TransformMatrix for GText (id: ", m_id, ").");
			return false;
		}

		if (!SetSize((float)m_textContainer.TextWidth(), (float)m_textContainer.TextHeight()))
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return false;
		}

		return true;
	}

  bool GText::Unload()
	{
		LOG("GText::Unload()");

		if (!m_textContainer.Unload())
		{
			echo("ERROR: Can't unload TextContainer for GText (id: ", m_id, ").");
			return false;
		}

		return true;
	}

  bool GText::Draw(Sprite& pSprite) const
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
				return false;
			}
		}

		return true;
	}

	D3DXVECTOR2 GText::GetOriginalSize() const
	{
		return GetSize();
	}

  bool GText::SetText(const std::string& pText)
	{
		LOG("GText::SetText()");

		if (!m_textContainer.SetText(pText))
		{
			echo("ERROR: Can't set text to TextContainer.");
			return false;
		}

		if (!SetSize((float)m_textContainer.TextWidth(), (float)m_textContainer.TextHeight()))
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return false;
		}

		return true;
	}

  bool GText::SetFont(const std::string& pFontName)
	{
		LOG("GText::SetFont()");

		if (!m_textContainer.SetFont(pFontName))
		{
			echo("ERROR: Can't set font for GText (id: ", m_id, ").");
			return false;
		}

		if (!SetSize((float)m_textContainer.TextWidth(), (float)m_textContainer.TextHeight()))
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return false;
		}

		return true;
	}


  bool GText::SetSize(float pWidth, float pHeight)
	{
		LOG("GText::SetSize()");

		if (!GBase::SetSize(pWidth, pHeight))
		{
			echo("ERROR: Can't set size for GText (id: ", m_id, ").");
			return false;
		}

		if (!m_textContainer.SetBasisPosition(D3DXVECTOR3(0, pHeight / 2, 0)))
		{
			echo("ERROR: Can't set basis for TextContainer.");
			return false;
		}

		return true;
	}

  bool GText::SetSize(const D3DXVECTOR2& pSize)
	{
		return SetSize(pSize.x, pSize.y);
	}

} // ns Doh3d
