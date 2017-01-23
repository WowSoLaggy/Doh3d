#pragma once

#ifndef INC_DOH3D_GPANEL_H
#define INC_DOH3D_GPANEL_H


#include "GBase.h"


namespace Doh3d
{

	class GPanel : public GBase
	{
	public:

		GPanel(float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName);
		virtual ~GPanel();

		virtual bool Load() override;
		virtual bool Unload() override;

		virtual bool Draw(Sprite& pSprite) const override;

		// Handlers

		virtual bool OnMouseMove(bool &pHandled) override;
		virtual bool OnMouseDown(bool &pHandled, int pButton) override;
		virtual bool OnMouseUp(bool &pHandled, int pButton) override;

	protected:

		int m_tiMain;
		std::string m_textureName;

		virtual D3DXVECTOR2 GetOriginalSize() const override;

	};

} // ns Doh3d


#endif // INC_DOH3D_GPANEL_H
