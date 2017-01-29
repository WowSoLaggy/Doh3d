//#include "Doh3d.h"
//#include "GBase.h"
//
//#include "InputMan.h"
//
//
//namespace Doh3d
//{
//
//	GBase::GBase()
//	{
//		static int nextId = 0;
//		d_id = nextId++;
//
//		d_isVisible = true;
//	}
//
//	GBase::~GBase()
//	{
//	}
//
//
//  bool GBase::updateTransformMatrix()
//	{
//		D3DXVECTOR2 sizeOrig = getOriginalSize();
//		D3DXVECTOR2 scaleCenter(d_position.x, d_position.y);
//
//		D3DXVECTOR2 scale;
//		if ((d_size.x <= 0) || (d_size.y <= 0))
//		{
//			d_size.x = sizeOrig.x;
//			d_size.y = sizeOrig.y;
//			scale = D3DXVECTOR2(1, 1);
//		}
//		else
//			scale = D3DXVECTOR2(d_size.x / sizeOrig.x, d_size.y / sizeOrig.y);
//
//		D3DXMatrixTransformation2D(&d_transformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);
//
//		return true;
//	}
//
//
//  bool GBase::onMouseMove(bool& pHandled)
//	{
//		if (containsPoint(InputMan::getCursorPosition()))
//			pHandled = true;
//
//		return true;
//	}
//
//  bool GBase::onMouseDown(bool& pHandled, int pButton)
//	{
//		if (containsPoint(InputMan::getCursorPosition()))
//			pHandled = true;
//
//		return true;
//	}
//
//  bool GBase::onMouseUp(bool& pHandled, int pButton)
//	{
//		if (containsPoint(InputMan::getCursorPosition()))
//			pHandled = true;
//
//		return true;
//	}
//
//  bool GBase::onKeyPressed(int pKey)
//	{
//		return true;
//	}
//
//  bool GBase::onKeyDown(int pKey)
//	{
//		return true;
//	}
//
//  bool GBase::onKeyUp(int pKey)
//	{
//		return true;
//	}
//
//
//	bool GBase::containsPoint(const D3DXVECTOR2& pPoint)
//	{
//		return Geometry::Rect(d_position.x, d_position.y, d_position.x + d_size.x, d_position.y + d_size.y).containsPoint(pPoint);
//	}
//
//
//  bool GBase::setSize(float pWidth, float pHeight)
//	{
//		d_size.x = pWidth;
//		d_size.y = pHeight;
//		return true;
//	}
//
//  bool GBase::setSize(const D3DXVECTOR2& pSize)
//	{
//		return setSize(pSize.x, pSize.y);
//	}
//
//} // ns Doh3d
