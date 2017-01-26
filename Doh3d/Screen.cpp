#include "Doh3d.h"
#include "Screen.h"

#include "RenderMan.h"


namespace Doh3d
{

	int Screen::getDesktopWidth()
	{
		RECT rectDesktop;
		HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &rectDesktop);
		return (rectDesktop.right - rectDesktop.left);
	}

	int Screen::getDesktopHeight()
	{
		RECT rectDesktop;
		HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &rectDesktop);
		return (rectDesktop.bottom - rectDesktop.top);
	}


	int Screen::getClientWidth()
	{
		return RenderMan::getRenderPars().resolutionWidth();
	}

	int Screen::getClientHeight()
	{
		return RenderMan::getRenderPars().resolutionHeight();
	}


	D3DXVECTOR2 Screen::getClientCenter()
	{
		return D3DXVECTOR2((FLOAT)(RenderMan::getRenderPars().resolutionWidth() / 2), (FLOAT)(RenderMan::getRenderPars().resolutionHeight() / 2));
	}

} // ns Doh3d
