#pragma once

#ifndef INC_DOH3D_RECT_H
#define INC_DOH3D_RECT_H


#include "Position2.h"
#include "Size2.h"


namespace Doh3d
{
	namespace Geometry
	{

		class RectI
		{
		public:

      RectI();
      RectI(int pLeft, int pTop, int pRight, int pBottom);
      RectI(const Position2& pPosition, const Size2& pSize);


			bool containsPoint(int pX, int pY) const;
			bool containsPoint(const Position2& pPoint) const;

			bool containsRect(const RectI& pRect) const;

		public:

      int d_left;
      int d_top;
      int d_right;
      int d_bottom;

      RectI operator + (const Position2& pOffset) const;
      RectI operator - (const Position2& pOffset) const;

		};

	} // ns Geometry
} // ns Doh3d


#endif // INC_DOH3D_RECT_H
