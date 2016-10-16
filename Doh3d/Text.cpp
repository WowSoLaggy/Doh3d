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


	ErrCode3d Text::Load()
	{
		LOG("Text::Load()");
		ErrCode3d err;

		err = CreateTexture();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't create texture for Text.");
			return err;
		}

		m_loaded = true;
		return err3d_noErr;
	}

	ErrCode3d Text::Unload()
	{
		LOG("Text::Unload()");
		ErrCode3d err;

		err = DisposeTexture();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't dispose texture for Text.");
			return err;
		}

		m_loaded = false;
		return err3d_noErr;
	}

	ErrCode3d Text::SetText(const std::string& pText)
	{
		LOG("Text::SetText()");
		ErrCode3d err;

		if (pText == m_text)
			return err3d_noErr;

		m_text = pText;

		if (m_loaded)
		{
			err = CreateTexture();
			if (err != err3d_noErr)
			{
				echo("ERROR: Can't create texture for Text.");
				return err;
			}
		}

		return err3d_noErr;
	}

	ErrCode3d Text::SetFont(const std::string& pFont)
	{
		LOG("Text::SetFont()");
		ErrCode3d err;

		if (pFont == m_font)
			return err3d_noErr;

		m_font = pFont;

		if (m_loaded)
		{
			err = CreateTexture();
			if (err != err3d_noErr)
			{
				echo("ERROR: Can't create texture for Text.");
				return err;
			}
		}

		return err3d_noErr;
	}

	ErrCode3d Text::CreateTexture()
	{
		LOG("Text::CreateTexture()");
		ErrCode3d err;

		err = DisposeTexture();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't dispose texture for Text.");
			return err;
		}

		if (m_text.empty())
			return err3d_noErr;

		err = ResourceMan::CreateFontTexture(m_text, m_font, m_texture, m_width, m_height, m_charOffsets);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get Text texture.");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d Text::DisposeTexture()
	{
		if (m_texture != nullptr)
		{
			m_texture->Release();
			m_texture = nullptr;
		}

		return err3d_noErr;
	}

} // ns Doh3d
