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

		bool HasText() const { return m_text.HasText(); }
		LPDIRECT3DTEXTURE9 GetTexture() const { return m_text.GetTexture(); }
		
    bool SetText(const std::string& pText);
    bool SetFont(const std::string& pFontName);
		
		int TextWidth() const { return m_text.Width(); }
		int TextHeight() const { return m_text.Height(); }


    bool SetBasisPosition(const D3DXVECTOR3& pPosition);
		const D3DXVECTOR3& GetPosition() const { return m_textPosition; }

    bool SetTextAlign(TextAlign pTextAlign);


    bool Load();
    bool Unload();

	private:

		D3DXVECTOR3 m_textBasis;
		D3DXVECTOR3 m_textPosition;
		TextAlign m_textAlign;
		class Text m_text;

    bool UpdatePosition();

	};

} // ns Doh3d


#endif // INC_DOH3D_TEXTCONTAINER_H
