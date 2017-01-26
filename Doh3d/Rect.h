#pragma once

#ifndef INC_DOH3D_RECT_H
#define INC_DOH3D_RECT_H


namespace Doh3d
{
	namespace Geometry
	{

		class Rect
		{
		public:

			Rect();
			Rect(float pLeft, float pTop, float pRight, float pBottom);


			bool containsPoint(float pX, float pY) const;
			bool containsPoint(const D3DXVECTOR2& pPoint) const;

			bool containsRect(const Rect& pRect) const;

		public:

      float d_left;
      float d_top;
      float d_right;
      float d_bottom;

			Rect operator + (const D3DXVECTOR2& pOffset) const;
			Rect operator - (const D3DXVECTOR2& pOffset) const;

		};

	} // ns Geometry
} // ns Doh3d


#endif // INC_DOH3D_RECT_H
