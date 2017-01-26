#include "Doh3d.h"
#include "Text.h"


#include "ResourceMan.h"


namespace Doh3d
{

	Text::Text()
	{
		d_loaded = false;
		d_text = "";
		d_font = "";
		d_texture = nullptr;
	}

	Text::~Text()
	{
		d_loaded = false;
		d_text = "";
		d_font = "";
		d_texture = nullptr;
	}


  bool Text::load()
	{
		LOG("Text::load()");

		if (!createTexture())
		{
			echo("ERROR: Can't create texture for Text.");
			return false;
		}

		d_loaded = true;
		return true;
	}

  bool Text::unload()
	{
		LOG("Text::unload()");

		if (!disposeTexture())
		{
			echo("ERROR: Can't dispose texture for Text.");
			return false;
		}

		d_loaded = false;
		return true;
	}

  bool Text::setText(const std::string& pText)
	{
		LOG("Text::setText()");

		if (pText == d_text)
			return true;

		d_text = pText;

		if (d_loaded)
		{
			if (!createTexture())
			{
				echo("ERROR: Can't create texture for Text.");
				return false;
			}
		}

		return true;
	}

  bool Text::setFont(const std::string& pFont)
	{
		LOG("Text::setFont()");

		if (pFont == d_font)
			return true;

		d_font = pFont;

		if (d_loaded)
		{
			if (!createTexture())
			{
				echo("ERROR: Can't create texture for Text.");
				return false;
			}
		}

		return true;
	}

  bool Text::createTexture()
	{
		LOG("Text::CreateTexture()");

		if (!disposeTexture())
		{
			echo("ERROR: Can't dispose texture for Text.");
			return false;
		}

		if (d_text.empty())
			return true;

		if (!ResourceMan::createFontTexture(d_text, d_font, d_texture, d_width, d_height, d_charOffsets))
		{
			echo("ERROR: Can't get Text texture.");
			return false;
		}

		return true;
	}

  bool Text::disposeTexture()
	{
		if (d_texture != nullptr)
		{
			d_texture->Release();
			d_texture = nullptr;
		}

		return true;
	}

} // ns Doh3d
