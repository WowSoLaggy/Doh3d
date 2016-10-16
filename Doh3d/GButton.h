#pragma once

#ifndef INC_DOH3D_GBUTTON_H
#define INC_DOH3D_GBUTTON_H


#include "GBase.h"
#include "Text.h"


namespace Doh3d
{

	class GButton : public GBase
	{
	public:

		GButton(float pPosX, float pPosY, float pSizeX, float pSizeY,
				const std::string& pTexNameNormal, const std::string& pTexNamePressed,
				const std::string& pTexNameSelected, const std::string& pTexNameDisabled);
		virtual ~GButton();

		virtual ErrCode3d Load();
		virtual ErrCode3d Unload();

		virtual ErrCode3d Draw(LPD3DXSPRITE pSprite);

		virtual ErrCode3d SetOnClickEvent(std::function<ErrCode3d()> pEvent);
		virtual ErrCode3d SetText(const std::string& pText);

		// Handlers

		virtual ErrCode3d Click();

		virtual ErrCode3d OnMouseMove(bool& pHandled);
		virtual ErrCode3d OnMouseDown(bool& pHandled, int pButton);
		virtual ErrCode3d OnMouseUp(bool& pHandled, int pButton);

	protected:

		std::string m_texNameNormal;
		std::string m_texNamePressed;
		std::string m_texNameSelected;
		std::string m_texNameDisabled;

		int m_tiNormal;
		int m_tiPressed;
		int m_tiSelected;
		int m_tiDisabled;

		GStates m_state;

		std::function<ErrCode3d()> OnClickEvent;

		Text m_text;
		D3DXVECTOR3 m_positionText;

		virtual D3DXVECTOR2 GetOriginalSize();

	};

} // ns Doh3d


#endif // INC_DOH3D_GBUTTON_H
