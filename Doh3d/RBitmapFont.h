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

		std::string getFontName() const { return d_fontName; }

		bool load();
    bool unload();

    bool getFontTexture(const std::string& pText, LPDIRECT3DTEXTURE9& pTexture, int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets);

	private:

		std::string d_fontName;
		std::string d_charsetPath;
		LPDIRECT3DTEXTURE9 d_charsetTexture;

		int d_lineHeight;
		int d_lineBase;

		std::vector<BitmapChar> d_chars;

    bool parseFntFile(const std::string& pFntPath);
	};

} // ns Doh3d


#endif // INC_DOH3D_BFONT_H
