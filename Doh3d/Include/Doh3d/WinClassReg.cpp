#include "..\Doh3d.h"
#include "WinClasReg.h"


namespace Doh3d
{

	void WinClassReg(StartupPars &pStartupPars)
	{
		WNDCLASS wc;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(6);
		wc.hCursor = LoadCursor(pStartupPars.hInstance, IDC_ARROW);
		wc.hIcon = LoadIcon(pStartupPars.hInstance, IDI_APPLICATION);
		wc.hInstance = pStartupPars.hInstance;
		wc.lpszClassName = pStartupPars.ApplicationName.c_str();
		wc.lpszMenuName = nullptr;
		RegisterClass(&wc);
	}

	void WinClassUnreg(StartupPars &pStartupPars)
	{
		UnregisterClass(pStartupPars.ApplicationName.c_str(), pStartupPars.hInstance);
	}

	LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
