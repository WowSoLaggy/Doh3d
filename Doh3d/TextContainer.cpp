#include "PrecompiledHeader.h"
#include "TextContainer.h"


namespace Doh3d
{

  bool TextContainer::updatePosition()
  {
    LOG(__FUNCTION__);

    d_textPosition = d_textBasis;
    d_textPosition -= Doh3d::Position2(0, d_text.height() / 2);

    switch (d_textAlign)
    {
    case TextAlign::Center:
    {
      d_textPosition -= Doh3d::Position2(d_text.width() / 2, 0);
      break;
    }
    case TextAlign::Right:
    {
      d_textPosition -= Doh3d::Position2(d_text.width(), 0);
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


  bool TextContainer::setBasisPosition(const Position2& pPosition)
  {
    d_textBasis = pPosition;

    if (!updatePosition())
      return false;

    return true;
  }

  bool TextContainer::setText(const std::string& pText)
  {
    if (!d_text.setText(pText))
      return false;

    if (!updatePosition())
      return false;

    return true;
  }

  bool TextContainer::setFont(const std::string& pFontName)
  {
    if (!d_text.setFont(pFontName))
      return false;

    if (!updatePosition())
      return false;

    return true;
  }

  bool TextContainer::setTextAlign(TextAlign pTextAlign)
  {
    d_textAlign = pTextAlign;

    if (!updatePosition())
      return false;

    return true;
  }


  RECT TextContainer::getRect() const
  {
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = textWidth();
    rect.bottom = textHeight();
    return rect;
  }

} // Doh3d
