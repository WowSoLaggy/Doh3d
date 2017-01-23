#pragma once

#ifndef INC_DOH3D_GTEXT_H
#define INC_DOH3D_GTEXT_H


#include "GBase.h"
#include "TextContainer.h"


namespace Doh3d
{

	class GText : public GBase
	{
	public:

		GText(float pPosX, float pPosY, const std::string& pText, const std::string& pFontName);
		virtual ~GText();

		virtual bool Load() override;
		virtual bool Unload() override;
		virtual bool Draw(Sprite& pSprite) const override;

		virtual bool SetSize(float pWidth, float pHeight) override;
		virtual bool SetSize(const D3DXVECTOR2& pSize) override;

		virtual bool SetText(const std::string& pText);
		virtual bool SetFont(const std::string& pFontName);

	protected:

		TextContainer m_textContainer;

		virtual D3DXVECTOR2 GetOriginalSize() const override;

	};

} // ns Doh3d


#endif // INC_DOH3D_GTEXT_H
