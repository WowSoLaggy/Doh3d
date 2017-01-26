#pragma once

#ifndef INC_DOH3D_TEXT_H
#define INC_DOH3D_TEXT_H


namespace Doh3d
{

	class Text
	{
	public:

		Text();
		~Text();

		int width() const { return d_width; }
		int height() const { return d_height; }

		bool hasText() const { return !d_text.empty(); }
		LPDIRECT3DTEXTURE9 getTexture() const { return d_texture; }

		bool load();
    bool unload();

    bool setText(const std::string& pText);
    bool setFont(const std::string& pFont);

		unsigned int getTextLength() const { return d_text.length(); }
		int getCharOffset(int pPos) const { return d_charOffsets[pPos]; }

	private:

		bool d_loaded;

		int d_width;
		int d_height;

		std::string d_text;
		std::string d_font;

		LPDIRECT3DTEXTURE9 d_texture;
		std::vector<int> d_charOffsets;

    bool createTexture();
    bool disposeTexture();
	};

} // ns Doh3d


#endif // INC_DOH3D_TEXT_H
