#pragma once

#ifndef INC_DOH3D_RECT_H
#define INC_DOH3D_RECT_H


namespace Doh3d
{
	namespace Geometry
	{

		struct Rect
		{
		public:

			Rect();

			Rect(float pLeft, float pTop, float pRight, float pBottom);


			float Left;
			float Top;
			float Right;
			float Bottom;


			bool ContainsPoint(float pX, float pY) const;
			bool ContainsPoint(const D3DXVECTOR2& pPoint) const;

			bool ContainsRect(const Rect& pRect) const;

		public:

			Rect operator + (const D3DXVECTOR2& pOffset) const;
			Rect operator - (const D3DXVECTOR2& pOffset) const;

		};

	} // ns Geometry
} // ns Doh3d


#endif // INC_DOH3D_RECT_H
