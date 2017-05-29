#include "PrecompiledHeader.h"
#include "Text.h"


#include "ResourceMan.h"


namespace Doh3d
{

	Text::Text()
	{
		d_text = "";
		d_font = "";
		d_texture = nullptr;
	}

	Text::~Text()
	{
		d_text = "";
		d_font = "";
		d_texture = nullptr;
	}


  bool Text::setText(const std::string& pText)
	{
    if (pText == d_text)
      return true;

    d_text = pText;

    if (!createTexture())
      return false;

    return true;
  }

  bool Text::setFont(const std::string& pFont)
	{
    if (pFont == d_font)
      return true;

    d_font = pFont;

    if (!createTexture())
      return false;

    return true;
	}

  bool Text::createTexture()
	{
		if (!disposeTexture())
			return false;

		if (d_text.empty())
			return true;

		if (!ResourceMan::createFontTexture(d_text, d_font, d_texture, d_width, d_height, d_charOffsets))
			return false;

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
