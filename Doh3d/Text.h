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

		int Width() const { return m_width; }
		int Height() const { return m_height; }

		bool IsText() const { return !m_text.empty(); }
		LPDIRECT3DTEXTURE9 GetTexture() const { return m_texture; }

		ErrCode3d Load();
		ErrCode3d Unload();

		ErrCode3d SetText(const std::string& pText);
		ErrCode3d SetFont(const std::string& pFont);

		unsigned int GetTextLength() const { return m_text.length(); }
		int GetCharOffset(int pPos) const { return m_charOffsets[pPos]; }

	private:

		bool m_loaded;

		int m_width;
		int m_height;

		std::string m_text;
		std::string m_font;

		LPDIRECT3DTEXTURE9 m_texture;
		std::vector<int> m_charOffsets;

		ErrCode3d CreateTexture();
		ErrCode3d DisposeTexture();
	};

} // ns Doh3d


#endif // INC_DOH3D_TEXT_H
