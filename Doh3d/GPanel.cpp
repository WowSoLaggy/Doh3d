#include "Doh3d.h"
#include "GPanel.h"

#include "ResourceMan.h"


namespace Doh3d
{

	GPanel::GPanel(float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName)
	{
		LOG("GPanel::GPanel()");

		d_position.x = roundf(pPosX);
		d_position.y = roundf(pPosY);
		d_position.z = 0;
		
		if (!setSize(pSizeX, pSizeY))
			echo("ERROR: Can't set size.");

		d_textureName = pTextureName;

		d_tiMain = 0;
	}

	GPanel::~GPanel()
	{
	}


  bool GPanel::load()
	{
		LOG("GPanel::load()");

		if (!ResourceMan::getTi(d_textureName, d_tiMain))
		{
			echo("ERROR: Can't get TI for panel (id: ", d_id, ").");
			return false;
		}

		if (!updateTransformMatrix())
		{
			echo("ERROR: Can't update TransformMatrix for button (id: ", d_id, ").");
			return false;
		}

		return true;
	}

  bool GPanel::unload()
	{
		return true;
	}

  bool GPanel::draw(Sprite& pSprite) const
	{
		LOG("GPanel::draw()");
		int hRes;

		pSprite.get()->SetTransform(&d_transformMatrix);

		hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_tiMain).get(), &ResourceMan::getTexture(d_tiMain).getFrame(0), 0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw sprite.");
			return false;
		}

		return true;
	}

	D3DXVECTOR2 GPanel::getOriginalSize() const
	{
		return ResourceMan::getTexture(d_tiMain).getSize();
	}


  bool GPanel::onMouseMove(bool &pHandled)
	{
		LOG("GPanel::onMouseMove()");

		if (!GBase::onMouseMove(pHandled))
		{
			echo("ERROR: Error occurred while GBase::onMouseMove().");
			return false;
		}

		return true;
	}

  bool GPanel::onMouseDown(bool &pHandled, int pButton)
	{
		LOG("GPanel::onMouseDown()");

		if (!GBase::onMouseDown(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::onMouseDown().");
			return false;
		}

		return true;
	}

  bool GPanel::onMouseUp(bool &pHandled, int pButton)
	{
		LOG("GPanel::onMouseUp()");

		if (!GBase::onMouseUp(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::onMouseUp().");
			return false;
		}

		return true;
	}

} // ns Doh3d
