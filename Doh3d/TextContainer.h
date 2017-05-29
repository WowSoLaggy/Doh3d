#pragma once

#ifndef INC_DOH3D_TEXTCONTAINER_H
#define INC_DOH3D_TEXTCONTAINER_H


#include "Text.h"


namespace Doh3d
{

  enum class TextAlign
  {
    Left,
    Center,
    Right,
  };


  class TextContainer
  {
  public:

    bool hasText() const { return d_text.hasText(); }
    LPDIRECT3DTEXTURE9 getTexture() const { return d_text.getTexture(); }
    RECT getRect() const;

    bool setText(const std::string& pText);
    bool setFont(const std::string& pFontName);

    int textWidth() const { return d_text.width(); }
    int textHeight() const { return d_text.height(); }


    bool setBasisPosition(const Position2& pPosition);
    const Position2& getPosition() const { return d_textPosition; }

    bool setTextAlign(TextAlign pTextAlign);

  private:

    Position2 d_textBasis;
    Position2 d_textPosition;
    TextAlign d_textAlign;
    class Text d_text;

    bool updatePosition();

  };

} // ns Doh3d


#endif // INC_DOH3D_TEXTCONTAINER_H
