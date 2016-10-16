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

		GText(float pPosX, float pPosY, const std::string& pText);
		virtual ~GText();

		virtual ErrCode3d Load();
		virtual ErrCode3d Unload();

		virtual ErrCode3d Draw(LPD3DXSPRITE pSprite);

		virtual ErrCode3d SetText(const std::string& pText);

	protected:

		Text m_text;
		D3DXVECTOR3 m_positionText;

		virtual D3DXVECTOR2 GetOriginalSize();

	};

} // ns Doh3d


#endif // INC_DOH3D_GTEXT_H
