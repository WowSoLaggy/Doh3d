#pragma once

#ifndef INC_DOH3D_BFONT_H
#define INC_DOH3D_BFONT_H


#include "BitmapChar.h"


namespace Doh3d
{

	class RBitmapFont
	{
	public:

		RBitmapFont(const std::string& pFontName);
		~RBitmapFont();

		std::string GetFontName() const { return m_fontName; }

		ErrCode3d Load();
		ErrCode3d Unload();

		ErrCode3d GetFontTexture(const std::string& pText, LPDIRECT3DTEXTURE9& pTexture, int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets);

	private:

		std::string m_fontName;
		std::string m_charsetPath;
		LPDIRECT3DTEXTURE9 m_charsetTexture;

		int m_lineHeight;
		int m_lineBase;

		std::vector<BitmapChar> m_chars;

		ErrCode3d ParseFntFile(const std::string& pFntPath);
	};

} // ns Doh3d


#endif // INC_DOH3D_BFONT_H
