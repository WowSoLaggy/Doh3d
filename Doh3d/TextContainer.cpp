#include "Doh3d.h"
#include "TextContainer.h"


namespace Doh3d
{

  bool TextContainer::Load()
  {
    LOG("TextContainer::Load()");

    if (!m_text.Load())
    {
      echo("ERROR: Can't load text.");
      return false;
    }

    if (!UpdatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::Unload()
  {
    LOG("TextContainer::Unload()");

    if (!m_text.Unload())
    {
      echo("ERROR: Can't unload text.");
      return false;
    }

    return true;
  }


  bool TextContainer::UpdatePosition()
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
      return false;
    }
    }

    return true;
  }


  bool TextContainer::SetBasisPosition(const D3DXVECTOR3& pPosition)
  {
    LOG("TextContainer::SetBasisPosition()");

    m_textBasis = pPosition;

    if (!UpdatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::SetText(const std::string& pText)
  {
    LOG("TextContainer::SetText()");

    if (!m_text.SetText(pText))
    {
      echo("ERROR: Can't set text.");
      return false;
    }

    if (!UpdatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::SetFont(const std::string& pFontName)
  {
    LOG("TextContainer::SetFont()");

    if (!m_text.SetFont(pFontName))
    {
      echo("ERROR: Can't set font.");
      return false;
    }

    if (!UpdatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

  bool TextContainer::SetTextAlign(TextAlign pTextAlign)
  {
    LOG("TextContainer::SetTextAlign()");

    m_textAlign = pTextAlign;

    if (!UpdatePosition())
    {
      echo("ERROR: Can't update position.");
      return false;
    }

    return true;
  }

} // Doh3d
