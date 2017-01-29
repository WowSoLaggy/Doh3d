//#pragma once
//
//#ifndef INC_DOH3D_GBUTTON_H
//#define INC_DOH3D_GBUTTON_H
//
//
//#include "GBase.h"
//#include "TextContainer.h"
//
//
//namespace Doh3d
//{
//
//	class GButton : public GBase
//	{
//	public:
//
//		GButton(float pPosX, float pPosY, float pSizeX, float pSizeY,
//				const std::string& pTexNameNormal, const std::string& pTexNamePressed,
//				const std::string& pTexNameSelected, const std::string& pTexNameDisabled);
//		virtual ~GButton();
//
//		virtual bool load() override;
//		virtual bool unload() override;
//
//		virtual bool draw(Sprite& pSprite) const override;
//
//		virtual bool setOnClickEvent(std::function<void()> pEvent);
//		virtual bool setText(const std::string& pText);
//		virtual bool setFont(const std::string& pFontName);
//
//		virtual void enable() { d_state = GStates::Normal; }
//		virtual void disable() { d_state = GStates::Disabled; }
//		virtual void setEnabled(bool pEnabled) { d_state = pEnabled ? GStates::Normal : GStates::Disabled; }
//		virtual bool isEnabled() { return d_state != GStates::Disabled; }
//
//		// Handlers
//
//		virtual bool click();
//
//		virtual bool onMouseMove(bool& pHandled) override;
//		virtual bool onMouseDown(bool& pHandled, int pButton) override;
//		virtual bool onMouseUp(bool& pHandled, int pButton) override;
//
//	protected:
//
//		std::string d_texNameNormal;
//		std::string d_texNamePressed;
//		std::string d_texNameSelected;
//		std::string d_texNameDisabled;
//
//		int d_tiNormal;
//		int d_tiPressed;
//		int d_tiSelected;
//		int d_tiDisabled;
//
//		GStates d_state;
//
//		TextContainer d_textContainer;
//
//
//		std::function<void()> onClickEvent;
//
//
//		virtual D3DXVECTOR2 getOriginalSize() const override;
//
//	};
//
//} // ns Doh3d
//
//
//#endif // INC_DOH3D_GBUTTON_H
