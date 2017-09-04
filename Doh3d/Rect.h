#pragma once

#ifndef INC_DOH3D_RECT_H
#define INC_DOH3D_RECT_H


#include "Vector2I.h"
#include "Size2I.h"


namespace Doh3d
{
	namespace Geometry
	{

		class RectI
		{
		public:

      RectI();
      RectI(int pLeft, int pTop, int pRight, int pBottom);
      RectI(const Vector2I& pPosition, const Size2I& pSize);


			bool containsPoint(int pX, int pY) const;
			bool containsPoint(const Vector2I& pPoint) const;

			bool containsRect(const RectI& pRect) const;

		public:

      int d_left;
      int d_top;
      int d_right;
      int d_bottom;

      RectI operator + (const Vector2I& pOffset) const;
      RectI operator - (const Vector2I& pOffset) const;

		};

	} // ns Geometry
} // ns Doh3d


#endif // INC_DOH3D_RECT_H
