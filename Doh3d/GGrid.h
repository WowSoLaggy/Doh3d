#pragma once

#ifndef INC_DOH3D_GGRID_H
#define INC_DOH3D_GGRID_H


#include "GBase.h"


namespace Doh3d
{

	class GridItem
	{
	public:
		virtual int GetTi() const PURE;
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

		virtual ErrCode3d Load() override;
		virtual ErrCode3d Unload() override;

		virtual ErrCode3d Draw(Sprite& pSprite) const override;


		virtual void SetFrameOffset(const D3DXVECTOR3& pFrameOffset) { m_frameOffset = pFrameOffset; }
		virtual void SetGridOffset(const D3DXVECTOR3& pGridOffset) { m_gridOffset = pGridOffset; }
		virtual void SetGridShift(const D3DXVECTOR3& pGridShift) { m_gridShift = pGridShift; }
		virtual void SetItemSize(const D3DXVECTOR3& pItemSize) { m_itemSize = pItemSize; }
		virtual GridItem* SelectCell(int pCellIndex);
		virtual int GetSelectedCell() const { return m_selectedCell; }
		virtual GridItem* GetItem(int pItemIndex);
		virtual GridItem* GetSelectedItem();

		std::vector<GridItem*>& Items() { return m_items; }
		const std::vector<GridItem*>& Items() const { return m_items; }


		// Handlers

		virtual ErrCode3d OnMouseMove(bool& pHandled) override;
		virtual ErrCode3d OnMouseDown(bool& pHandled, int pButton) override;
		virtual ErrCode3d OnMouseUp(bool& pHandled, int pButton) override;


		// Events

		std::function<void(void)> OnSelectedItemChanged;

	protected:

		std::string m_textureName;
		std::string m_frameTextureName;
		int m_ti;
		int m_tiFrame;

		D3DXVECTOR3 m_frameOffset;
		D3DXVECTOR3 m_gridOffset;
		D3DXVECTOR3 m_gridShift;
		D3DXVECTOR3 m_itemSize;
		int m_numberOfCells;
		int m_selectedCell;

		std::vector<GridItem*> m_items;

		virtual D3DXVECTOR2 GetOriginalSize() const override;
	};

} // ns Doh3d


#endif // INC_DOH3D_GGRID_H
