#pragma once

#ifndef INC_DOH3D_GBASE_H
#define INC_DOH3D_GBASE_H


#include "ErrCodes3d.h"


namespace Doh3d
{

	enum class GStates
	{
		Normal,
		Pressed,
		Selected,
		Disabled,

		End
	};


	class GBase
	{
	public:

		virtual ~GBase();

		int Id() const { return m_id; }
		bool IsVisible() const { return m_isVisible; }

		virtual ErrCode3d Load() PURE;
		virtual ErrCode3d Unload() PURE;


		virtual ErrCode3d Draw(Sprite& pSprite) const PURE;


		bool& Visible() { return m_isVisible; }
		const bool& Visible() const { return m_isVisible; }

		D3DXVECTOR3& Position() { return m_position; }
		const D3DXVECTOR3& Position() const { return m_position; }

		// Handlers

		virtual ErrCode3d OnMouseMove(bool& pHandled);
		virtual ErrCode3d OnMouseDown(bool& pHandled, int pButton);
		virtual ErrCode3d OnMouseUp(bool& pHandled, int pButton);

		virtual ErrCode3d OnKeyPressed(int pKey);
		virtual ErrCode3d OnKeyDown(int pKey);
		virtual ErrCode3d OnKeyUp(int pKey);

	protected:

		GBase();

		int m_id;
		bool m_isVisible;

		D3DXVECTOR3 m_position;
		D3DXVECTOR2 m_size;

		virtual D3DXVECTOR2 GetOriginalSize() const PURE;
		virtual bool ContainsPoint(D3DXVECTOR2 pPoint);

		D3DXMATRIX m_transformMatrix;
		ErrCode3d UpdateTransformMatrix();

	};

} // ns Doh3d


#endif // INC_DOH3D_GBASE_H
