#pragma once

#ifndef INC_DOH3D_BCHAR_H
#define INC_DOH3D_BCHAR_H


namespace Doh3d
{

	struct BitmapChar
	{
		char Id;

		int X;
		int Y;

		int Width;
		int Height;

		int OffsetX;
		int OffsetY;

		int AdvanceX;
	};

} // Doh3d


#endif // INC_DOH3D_BCHAR_H
