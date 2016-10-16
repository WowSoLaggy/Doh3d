#pragma once

#ifndef INC_DOH3D_SCREEN_H
#define INC_DOH3D_SCREEN_H


namespace Doh3d
{

	class Screen
	{
	public:

		static int GetDesktopWidth();
		static int GetDesktopHeight();

		static int GetClientWidth();
		static int GetClientHeight();

		static D3DXVECTOR2 GetClientCenter();

	};

} // ns Doh3d


#endif // INC_DOH3D_SCREEN_H
