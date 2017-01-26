#include "Doh3d.h"
#include "GGrid.h"


namespace Doh3d
{

	GGrid::GGrid(float pPosX, float pPosY, float pSizeX, float pSizeY, int pNumberOfCells,
				 const std::string& pTextureName, const std::string& pFrameTextureName)
	{
		LOG("GGrid::GGrid()");

		d_position.x = roundf(pPosX);
		d_position.y = roundf(pPosY);
		d_position.z = 0;
		
		if (!setSize(pSizeX, pSizeY))
			echo("ERROR: Can't set size.");

		d_textureName = pTextureName;
		d_frameTextureName = pFrameTextureName;
		d_ti = 0;
		d_tiFrame = 0;

		d_numberOfCells = pNumberOfCells;
		d_selectedCell = -1;
		d_items.resize(pNumberOfCells, nullptr);

		onSelectedItemChanged = nullptr;
	}
	
	GGrid::~GGrid() { }


  bool GGrid::load()
	{
		LOG("GGrid::load()");

		if (!ResourceMan::getTi(d_textureName, d_ti))
		{
			echo("ERROR: Can't get TI for GGrid (id: ", d_id, "): \"", d_textureName, "\".");
			return false;
		}

		if (!ResourceMan::getTi(d_frameTextureName, d_tiFrame))
		{
			echo("ERROR: Can't get TI for GGrid frame (id: ", d_id, "): \"", d_textureName, "\".");
			return false;
		}

		if (!updateTransformMatrix())
		{
			echo("ERROR: Can't update TransformMatrix for GGrid (id: ", d_id, ").");
			return false;
		}

		return true;
	}

  bool GGrid::unload()
	{
		return true;
	}


  bool GGrid::draw(Sprite& pSprite) const
	{
		LOG("GGrid::draw()");
		int hRes;

		pSprite.get()->SetTransform(&d_transformMatrix);

		hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_ti).get(), &ResourceMan::getTexture(d_ti).getFrame(0), 0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw sprite.");
			return false;
		}

		// Selection frame

		if (d_selectedCell != -1)
		{
			D3DXVECTOR3 framePos = d_position + d_frameOffset + d_gridShift * (FLOAT)d_selectedCell;
			hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_tiFrame).get(), &ResourceMan::getTexture(d_tiFrame).getFrame(0), 0, &(framePos), D3DCOLOR_ARGB(255, 255, 255, 255));
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw sprite.");
				return false;
			}
		}

		// Items

		int cellNumber = -1;
		for (auto* pItem : d_items)
		{
			++cellNumber;
			if (!pItem) continue;

			D3DXVECTOR3 framePos = d_position + d_gridOffset + d_gridShift * (FLOAT)cellNumber + d_itemSize2;
			framePos.x -= ResourceMan::getTexture(pItem->getTi()).getSize2().x;
			framePos.y -= ResourceMan::getTexture(pItem->getTi()).getSize2().y;
			hRes = pSprite.get()->Draw(ResourceMan::getTexture(pItem->getTi()).get(), &ResourceMan::getTexture(pItem->getTi()).getFrame(0), 0, &(framePos), D3DCOLOR_ARGB(255, 255, 255, 255));
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw sprite.");
				return false;
			}
		}

		return true;
	}


  bool GGrid::onMouseMove(bool& pHandled)
	{
		LOG("GGrid::onMouseMove()");

		if (!GBase::onMouseMove(pHandled))
		{
			echo("ERROR: Error occurred while GBase::onMouseMove().");
			return false;
		}

		return true;
	}

  bool GGrid::onMouseDown(bool& pHandled, int pButton)
	{
		LOG("GGrid::onMouseDown()");

		if (!GBase::onMouseDown(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::onMouseDown().");
			return false;
		}

		int cellNumber = -1;
		for (auto* pItem : d_items)
		{
			++cellNumber;
			if (!pItem) continue;

			D3DXVECTOR3 itemTopLeft = d_position + d_gridOffset + d_gridShift * (FLOAT)cellNumber;
			if (Geometry::Rect(itemTopLeft.x, itemTopLeft.y, itemTopLeft.x + d_itemSize.x, itemTopLeft.y + d_itemSize.y).containsPoint(InputMan::getCursorPosition()))
			{
				selectCell(cellNumber);
				break;
			}
		}

		return true;
	}

  bool GGrid::onMouseUp(bool& pHandled, int pButton)
	{
		LOG("GButton::onMouseUp()");

		if (!GBase::onMouseUp(pHandled, pButton))
		{
			echo("ERROR: Error occurred while GBase::onMouseUp().");
			return false;
		}

		return true;
	}


	D3DXVECTOR2 GGrid::getOriginalSize() const
	{
		return ResourceMan::getTexture(d_ti).getSize();
	}


	GridItem* GGrid::selectCell(int pCellIndex)
	{
		if (pCellIndex < -1 || pCellIndex >= d_numberOfCells)
			return nullptr;

		d_selectedCell = pCellIndex;

		if (onSelectedItemChanged != nullptr)
			onSelectedItemChanged();

		return getSelectedItem();
	}

	GridItem* GGrid::getItem(int pItemIndex)
	{
		if (pItemIndex < 0 || pItemIndex >= (int)d_items.size())
			return nullptr;
		return d_items[pItemIndex];
	}

	GridItem* GGrid::getSelectedItem()
	{
		return d_selectedCell == -1 ? nullptr : d_items[d_selectedCell];
	}

} // ns Doh3d
