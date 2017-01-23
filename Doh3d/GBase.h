#pragma once

#ifndef INC_DOH3D_GBASE_H
#define INC_DOH3D_GBASE_H


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

		virtual bool Load() PURE;
		virtual bool Unload() PURE;
		virtual bool Draw(Sprite& pSprite) const PURE;

		virtual bool SetSize(float pWidth, float pHeight);
		virtual bool SetSize(const D3DXVECTOR2& pSize);

		const D3DXVECTOR2& GetSize() const { return m_size; }


		bool& IsVisible() { return m_isVisible; }
		const bool& IsVisible() const { return m_isVisible; }

		D3DXVECTOR3& Position() { return m_position; }
		const D3DXVECTOR3& Position() const { return m_position; }

		// Handlers

		virtual bool OnMouseMove(bool& pHandled);
		virtual bool OnMouseDown(bool& pHandled, int pButton);
		virtual bool OnMouseUp(bool& pHandled, int pButton);

		virtual bool OnKeyPressed(int pKey);
		virtual bool OnKeyDown(int pKey);
		virtual bool OnKeyUp(int pKey);

	protected:

		GBase();

		int m_id;
		bool m_isVisible;

		D3DXVECTOR3 m_position;

		virtual D3DXVECTOR2 GetOriginalSize() const PURE;
		virtual bool ContainsPoint(const D3DXVECTOR2& pPoint);

		D3DXMATRIX m_transformMatrix;
    bool UpdateTransformMatrix();

	private:

		D3DXVECTOR2 m_size;

	};

} // ns Doh3d


#endif // INC_DOH3D_GBASE_H
