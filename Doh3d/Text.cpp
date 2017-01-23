#include "Doh3d.h"
#include "Text.h"


#include "ResourceMan.h"


namespace Doh3d
{

	Text::Text()
	{
		m_loaded = false;
		m_text = "";
		m_font = "";
		m_texture = nullptr;
	}

	Text::~Text()
	{
		m_loaded = false;
		m_text = "";
		m_font = "";
		m_texture = nullptr;
	}


  bool Text::Load()
	{
		LOG("Text::Load()");

		if (!CreateTexture())
		{
			echo("ERROR: Can't create texture for Text.");
			return false;
		}

		m_loaded = true;
		return true;
	}

  bool Text::Unload()
	{
		LOG("Text::Unload()");

		if (!DisposeTexture())
		{
			echo("ERROR: Can't dispose texture for Text.");
			return false;
		}

		m_loaded = false;
		return true;
	}

  bool Text::SetText(const std::string& pText)
	{
		LOG("Text::SetText()");

		if (pText == m_text)
			return true;

		m_text = pText;

		if (m_loaded)
		{
			if (!CreateTexture())
			{
				echo("ERROR: Can't create texture for Text.");
				return false;
			}
		}

		return true;
	}

  bool Text::SetFont(const std::string& pFont)
	{
		LOG("Text::SetFont()");

		if (pFont == m_font)
			return true;

		m_font = pFont;

		if (m_loaded)
		{
			if (!CreateTexture())
			{
				echo("ERROR: Can't create texture for Text.");
				return false;
			}
		}

		return true;
	}

  bool Text::CreateTexture()
	{
		LOG("Text::CreateTexture()");

		if (!DisposeTexture())
		{
			echo("ERROR: Can't dispose texture for Text.");
			return false;
		}

		if (m_text.empty())
			return true;

		if (!ResourceMan::CreateFontTexture(m_text, m_font, m_texture, m_width, m_height, m_charOffsets))
		{
			echo("ERROR: Can't get Text texture.");
			return false;
		}

		return true;
	}

  bool Text::DisposeTexture()
	{
		if (m_texture != nullptr)
		{
			m_texture->Release();
			m_texture = nullptr;
		}

		return true;
	}

} // ns Doh3d
