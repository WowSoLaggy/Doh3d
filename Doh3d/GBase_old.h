//#pragma once
//
//#ifndef INC_DOH3D_GBASE_H
//#define INC_DOH3D_GBASE_H
//
//
//namespace Doh3d
//{
//
//	enum class GStates
//	{
//		Normal,
//		Pressed,
//		Selected,
//		Disabled,
//
//		End
//	};
//
//
//	class GBase
//	{
//	public:
//
//		virtual ~GBase();
//
//		int id() const { return d_id; }
//
//		virtual bool load() PURE;
//		virtual bool unload() PURE;
//		virtual bool draw(Sprite& pSprite) const PURE;
//
//		virtual bool setSize(float pWidth, float pHeight);
//		virtual bool setSize(const D3DXVECTOR2& pSize);
//
//		const D3DXVECTOR2& getSize() const { return d_size; }
//
//
//		bool& isVisible() { return d_isVisible; }
//		const bool& isVisible() const { return d_isVisible; }
//
//		D3DXVECTOR3& position() { return d_position; }
//		const D3DXVECTOR3& position() const { return d_position; }
//
//		// Handlers
//
//		virtual bool onMouseMove(bool& pHandled);
//		virtual bool onMouseDown(bool& pHandled, int pButton);
//		virtual bool onMouseUp(bool& pHandled, int pButton);
//
//		virtual bool onKeyPressed(int pKey);
//		virtual bool onKeyDown(int pKey);
//		virtual bool onKeyUp(int pKey);
//
//	protected:
//
//		GBase();
//
//		int d_id;
//		bool d_isVisible;
//
//		D3DXVECTOR3 d_position;
//
//		virtual D3DXVECTOR2 getOriginalSize() const PURE;
//		virtual bool containsPoint(const D3DXVECTOR2& pPoint);
//
//		D3DXMATRIX d_transformMatrix;
//    bool updateTransformMatrix();
//
//	private:
//
//		D3DXVECTOR2 d_size;
//
//	};
//
//} // ns Doh3d
//
//
//#endif // INC_DOH3D_GBASE_H
