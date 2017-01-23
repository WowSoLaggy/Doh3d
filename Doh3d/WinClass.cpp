#include "Doh3d.h"
#include "WinClass.h"


namespace Doh3d
{
	
	void WinClass::registerClass(const StartupPars& pStartupPars, const std::string& pApplicationName)
	{
		d_startupPars = pStartupPars;
		d_applicationName = pApplicationName;

		WNDCLASS wc;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(6);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(pStartupPars.hInstance, IDI_APPLICATION);
		wc.hInstance = pStartupPars.hInstance;
		wc.lpszClassName = d_applicationName.c_str();
		wc.lpszMenuName = nullptr;
		RegisterClass(&wc);
	}

	void WinClass::unregisterClass()
	{
		UnregisterClass(d_applicationName.c_str(), d_startupPars.hInstance);
	}

	LRESULT __stdcall WinClass::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

} // ns Doh3d
