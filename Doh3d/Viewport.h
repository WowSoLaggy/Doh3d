#pragma once

#ifndef INC_DOH3D_VIEWPORT_H
#define INC_DOH3D_VIEWPORT_H


namespace Doh3d
{

	struct Viewport
	{
		float PositionX;
		float PositionY;

		float Width2;
		float Height2;

		float Left() const { return PositionX - Width2; }
		float Top() const { return PositionY - Height2; }
		float Right() const { return PositionX + Width2; }
		float Bottom() const { return PositionY + Height2; }
	};

} // ns Doh3d


#endif // INC_DOH3D_VIEWPORT_H
