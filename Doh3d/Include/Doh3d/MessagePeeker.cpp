#include "..\Doh3d.h"
#include "MessagePeeker.h"


namespace Doh3d
{

	UINT WinPeekMessage()
	{
		MSG msg;
		UINT res = 0;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			res = msg.message;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return res;
	}

} // ns Doh3d
