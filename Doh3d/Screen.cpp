#include "Doh3d.h"
#include "Screen.h"

#include "RenderMan.h"


namespace Doh3d
{

	int Screen::GetDesktopWidth()
	{
		RECT rectDesktop;
		HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &rectDesktop);
		return (rectDesktop.right - rectDesktop.left);
	}

	int Screen::GetDesktopHeight()
	{
		RECT rectDesktop;
		HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &rectDesktop);
		return (rectDesktop.bottom - rectDesktop.top);
	}


	int Screen::GetClientWidth()
	{
		return RenderMan::GetRenderPars().ResolutionWidth;
	}

	int Screen::GetClientHeight()
	{
		return RenderMan::GetRenderPars().ResolutionHeight;
	}


	D3DXVECTOR2 Screen::GetClientCenter()
	{
		return D3DXVECTOR2((FLOAT)(RenderMan::GetRenderPars().ResolutionWidth / 2), (FLOAT)(RenderMan::GetRenderPars().ResolutionHeight / 2));
	}

} // ns Doh3d
