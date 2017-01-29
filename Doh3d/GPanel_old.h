//#pragma once
//
//#ifndef INC_DOH3D_GPANEL_H
//#define INC_DOH3D_GPANEL_H
//
//
//#include "GBase.h"
//
//
//namespace Doh3d
//{
//
//	class GPanel : public GBase
//	{
//	public:
//
//		GPanel(float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName);
//		virtual ~GPanel();
//
//		virtual bool load() override;
//		virtual bool unload() override;
//
//		virtual bool draw(Sprite& pSprite) const override;
//
//		// Handlers
//
//		virtual bool onMouseMove(bool& pHandled) override;
//		virtual bool onMouseDown(bool& pHandled, int pButton) override;
//		virtual bool onMouseUp(bool& pHandled, int pButton) override;
//
//	protected:
//
//		int d_tiMain;
//		std::string d_textureName;
//
//		virtual D3DXVECTOR2 getOriginalSize() const override;
//
//	};
//
//} // ns Doh3d
//
//
//#endif // INC_DOH3D_GPANEL_H
