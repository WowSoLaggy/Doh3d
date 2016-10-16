#include "Doh3d.h"
#include "GBase.h"

#include "InputMan.h"


namespace Doh3d
{

	GBase::GBase()
	{
		static int m_nextId = 0;
		m_id = m_nextId++;

		m_isVisible = true;
	}

	GBase::~GBase()
	{
	}


	ErrCode3d GBase::SetVisible(bool pVisible)
	{
		m_isVisible = pVisible;
		return err3d_noErr;
	}


	ErrCode3d GBase::UpdateTransformMatrix()
	{
		D3DXVECTOR2 sizeOrig = GetOriginalSize();
		D3DXVECTOR2 scaleCenter(m_position.x, m_position.y);

		D3DXVECTOR2 scale;
		if ((m_size.x <= 0) || (m_size.y <= 0))
		{
			m_size.x = sizeOrig.x;
			m_size.y = sizeOrig.y;
			scale = D3DXVECTOR2(1, 1);
		}
		else
			scale = D3DXVECTOR2(m_size.x / sizeOrig.x, m_size.y / sizeOrig.y);

		D3DXMatrixTransformation2D(&m_transformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);

		return err3d_noErr;
	}


	ErrCode3d GBase::OnMouseMove(bool& pHandled)
	{
		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			pHandled = true;
			return err3d_noErr;
		}

		pHandled = false;
		return err3d_noErr;
	}

	ErrCode3d GBase::OnMouseDown(bool& pHandled, int pButton)
	{
		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			pHandled = true;
			return err3d_noErr;
		}

		pHandled = false;
		return err3d_noErr;
	}

	ErrCode3d GBase::OnMouseUp(bool& pHandled, int pButton)
	{
		if (ContainsPoint(InputMan::GetCursorPosition()))
		{
			pHandled = true;
			return err3d_noErr;
		}

		pHandled = false;
		return err3d_noErr;
	}

	ErrCode3d GBase::OnKeyPressed(int pKey)
	{
		return err3d_noErr;
	}

	ErrCode3d GBase::OnKeyDown(int pKey)
	{
		return err3d_noErr;
	}

	ErrCode3d GBase::OnKeyUp(int pKey)
	{
		return err3d_noErr;
	}


	bool GBase::ContainsPoint(D3DXVECTOR2 pPoint)
	{
		if ((pPoint.x < m_position.x) || (m_position.x + m_size.x < pPoint.x) || (pPoint.y < m_position.y) || (m_position.y + m_size.y < pPoint.y))
			return false;

		return true;
	}

} // ns Doh3d
