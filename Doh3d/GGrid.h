#pragma once

#ifndef INC_DOH3D_GGRID_H
#define INC_DOH3D_GGRID_H


#include "GBase.h"


namespace Doh3d
{

	class GridItem
	{
	public:
		virtual int getTi() const PURE;
	protected:
		GridItem() { }
		virtual ~GridItem() { }
	};


	class GGrid : public GBase
	{
	public:

		GGrid(float pPosX, float pPosY, float pSizeX, float pSizeY, int pNumberOfCells,
			  const std::string& pTextureName, const std::string& pFrameTextureName);
		virtual ~GGrid();

		virtual bool load() override;
		virtual bool unload() override;

		virtual bool draw(Sprite& pSprite) const override;


		virtual void setFrameOffset(const D3DXVECTOR3& pFrameOffset) { d_frameOffset = pFrameOffset; }
		virtual void setGridOffset(const D3DXVECTOR3& pGridOffset) { d_gridOffset = pGridOffset; }
		virtual void setGridShift(const D3DXVECTOR3& pGridShift) { d_gridShift = pGridShift; }
		virtual void setItemSize(const D3DXVECTOR3& pItemSize) { d_itemSize = pItemSize; d_itemSize2 = d_itemSize / 2; }
		virtual GridItem* selectCell(int pCellIndex);
		virtual int getSelectedCell() const { return d_selectedCell; }
		virtual GridItem* getItem(int pItemIndex);
		virtual GridItem* getSelectedItem();

		std::vector<GridItem*>& items() { return d_items; }
		const std::vector<GridItem*>& items() const { return d_items; }


		// Handlers

		virtual bool onMouseMove(bool& pHandled) override;
		virtual bool onMouseDown(bool& pHandled, int pButton) override;
		virtual bool onMouseUp(bool& pHandled, int pButton) override;


		// Events

		std::function<void(void)> onSelectedItemChanged;

	protected:

		std::string d_textureName;
		std::string d_frameTextureName;
		int d_ti;
		int d_tiFrame;

		D3DXVECTOR3 d_frameOffset;
		D3DXVECTOR3 d_gridOffset;
		D3DXVECTOR3 d_gridShift;
		D3DXVECTOR3 d_itemSize;
		D3DXVECTOR3 d_itemSize2;
		int d_numberOfCells;
		int d_selectedCell;

		std::vector<GridItem*> d_items;

		virtual D3DXVECTOR2 getOriginalSize() const override;
	};

} // ns Doh3d


#endif // INC_DOH3D_GGRID_H
