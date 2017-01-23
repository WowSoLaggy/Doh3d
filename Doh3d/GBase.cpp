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


  bool GBase::UpdateTransformMatrix()
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

		return true;
	}


  bool GBase::OnMouseMove(bool& pHandled)
	{
		if (ContainsPoint(InputMan::GetCursorPosition()))
			pHandled = true;

		return true;
	}

  bool GBase::OnMouseDown(bool& pHandled, int pButton)
	{
		if (ContainsPoint(InputMan::GetCursorPosition()))
			pHandled = true;

		return true;
	}

  bool GBase::OnMouseUp(bool& pHandled, int pButton)
	{
		if (ContainsPoint(InputMan::GetCursorPosition()))
			pHandled = true;

		return true;
	}

  bool GBase::OnKeyPressed(int pKey)
	{
		return true;
	}

  bool GBase::OnKeyDown(int pKey)
	{
		return true;
	}

  bool GBase::OnKeyUp(int pKey)
	{
		return true;
	}


	bool GBase::ContainsPoint(const D3DXVECTOR2& pPoint)
	{
		return Geometry::Rect(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y).ContainsPoint(pPoint);
	}


  bool GBase::SetSize(float pWidth, float pHeight)
	{
		m_size.x = pWidth;
		m_size.y = pHeight;
		return true;
	}

  bool GBase::SetSize(const D3DXVECTOR2& pSize)
	{
		return SetSize(pSize.x, pSize.y);
	}

} // ns Doh3d
