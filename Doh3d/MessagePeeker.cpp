#include "Doh3d.h"
#include "MessagePeeker.h"


namespace Doh3d
{

	bool WinPeekExit()
	{
		MSG msg;
		UINT res = 0;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			res = msg.message;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return (res == WM_QUIT);
	}

} // ns Doh3d
