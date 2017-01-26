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

		virtual bool load() override;
		virtual bool unload() override;
		virtual bool draw(Sprite& pSprite) const override;

		virtual bool setSize(float pWidth, float pHeight) override;
		virtual bool setSize(const D3DXVECTOR2& pSize) override;

		virtual bool setText(const std::string& pText);
		virtual bool setFont(const std::string& pFontName);

	protected:

		TextContainer d_textContainer;

		virtual D3DXVECTOR2 getOriginalSize() const override;

	};

} // ns Doh3d


#endif // INC_DOH3D_GTEXT_H
