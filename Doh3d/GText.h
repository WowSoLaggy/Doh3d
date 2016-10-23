#pragma once

#ifndef INC_DOH3D_GTEXT_H
#define INC_DOH3D_GTEXT_H


#include "GBase.h"
#include "Text.h"


namespace Doh3d
{

	class GText : public GBase
	{
	public:

		GText(float pPosX, float pPosY, const std::string& pText, const std::string& pFontName);
		virtual ~GText();

		virtual ErrCode3d Load() override;
		virtual ErrCode3d Unload() override;

		virtual ErrCode3d Draw(Sprite& pSprite) const override;

		virtual ErrCode3d SetText(const std::string& pText);
		virtual ErrCode3d SetFont(const std::string& pFontName);

	protected:

		Text m_text;
		D3DXVECTOR3 m_positionText;

		virtual D3DXVECTOR2 GetOriginalSize() const override;

	};

} // ns Doh3d


#endif // INC_DOH3D_GTEXT_H
