#include "Doh3d.h"
#include "TextContainer.h"


namespace Doh3d
{

  bool TextContainer::load()
  {
    LOG("TextContainer::load()");

    if (!d_text.load())
    {
      echo("ERROR: Can't load text.");
      return false;
    }

    if (!updatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::unload()
  {
    LOG("TextContainer::unload()");

    if (!d_text.unload())
    {
      echo("ERROR: Can't unload text.");
      return false;
    }

    return true;
  }


  bool TextContainer::updatePosition()
  {
    LOG("TextContainer::updatePosition()");

    d_textPosition = d_textBasis;
    d_textPosition.y -= d_text.height() / 2;

    switch (d_textAlign)
    {
    case TextAlign::Center:
    {
      d_textPosition.x -= d_text.width() / 2;
      break;
    }
    case TextAlign::Right:
    {
      d_textPosition.x -= d_text.width();
      break;
    }
    case TextAlign::Left:
    {
      break;
    }
    default:
    {
      echo("ERROR: Invalid TextAlign value.");
      return false;
    }
    }

    return true;
  }


  bool TextContainer::setBasisPosition(const D3DXVECTOR3& pPosition)
  {
    LOG("TextContainer::setBasisPosition()");

    d_textBasis = pPosition;

    if (!updatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::setText(const std::string& pText)
  {
    LOG("TextContainer::setText()");

    if (!d_text.setText(pText))
    {
      echo("ERROR: Can't set text.");
      return false;
    }

    if (!updatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::setFont(const std::string& pFontName)
  {
    LOG("TextContainer::setFont()");

    if (!d_text.setFont(pFontName))
    {
      echo("ERROR: Can't set font.");
      return false;
    }

    if (!updatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::setTextAlign(TextAlign pTextAlign)
  {
    LOG("TextContainer::setTextAlign()");

    d_textAlign = pTextAlign;

    if (!updatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

} // Doh3d
