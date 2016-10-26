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

		virtual ErrCode3d Load() override;
		virtual ErrCode3d Unload() override;

		virtual ErrCode3d Draw(Sprite& pSprite) const override;

		virtual ErrCode3d SetOnClickEvent(std::function<void()> pEvent);
		virtual ErrCode3d SetText(const std::string& pText);
		virtual ErrCode3d SetFont(const std::string& pFontName);

		virtual void Enable() { m_state = GStates::Normal; }
		virtual void Disable() { m_state = GStates::Disabled; }
		virtual void SetEnabled(bool pEnabled) { m_state = pEnabled ? GStates::Normal : GStates::Disabled; }
		virtual bool IsEnabled() { return m_state != GStates::Disabled; }

		// Handlers

		virtual ErrCode3d Click();

		virtual ErrCode3d OnMouseMove(bool& pHandled) override;
		virtual ErrCode3d OnMouseDown(bool& pHandled, int pButton) override;
		virtual ErrCode3d OnMouseUp(bool& pHandled, int pButton) override;

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

		std::function<void()> OnClickEvent;

		Text m_text;
		D3DXVECTOR3 m_positionText;

		virtual D3DXVECTOR2 GetOriginalSize() const override;

	};

} // ns Doh3d


#endif // INC_DOH3D_GBUTTON_H
