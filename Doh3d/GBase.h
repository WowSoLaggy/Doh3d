#pragma once

#ifndef INC_DOH3D_GBASE_H
#define INC_DOH3D_GBASE_H


#include "ErrCodes3d.h"


namespace Doh3d
{

	enum GStates : int
	{
		gstate_normal = 0,
		gstate_pressed,
		gstate_selected,
		gstate_disabled,

		gstate_end
	};


	class GBase
	{
	public:

		int Id() const { return m_id; }
		bool IsVisible() const { return m_isVisible; }

		virtual ErrCode3d Load() PURE;
		virtual ErrCode3d Unload() PURE;


		virtual ErrCode3d Draw(LPD3DXSPRITE pSprite) PURE;

		virtual ErrCode3d SetVisible(bool pVisible);

		// Handlers

		virtual ErrCode3d OnMouseMove(bool& pHandled);
		virtual ErrCode3d OnMouseDown(bool& pHandled, int pButton);
		virtual ErrCode3d OnMouseUp(bool& pHandled, int pButton);

		virtual ErrCode3d OnKeyPressed(int pKey);
		virtual ErrCode3d OnKeyDown(int pKey);
		virtual ErrCode3d OnKeyUp(int pKey);

	protected:

		GBase();
		virtual ~GBase();

		int m_id;
		bool m_isVisible;

		D3DXVECTOR3 m_position;
		D3DXVECTOR2 m_size;

		virtual D3DXVECTOR2 GetOriginalSize() PURE;
		virtual bool ContainsPoint(D3DXVECTOR2 pPoint);

		D3DXMATRIX m_transformMatrix;
		ErrCode3d UpdateTransformMatrix();

	};

} // ns Doh3d


#endif // INC_DOH3D_GBASE_H
