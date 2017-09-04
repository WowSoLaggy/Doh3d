#include "PrecompiledHeader.h"
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


  Position2I Screen::getClientCenter()
	{
		return Position2I(RenderMan::getRenderPars().resolutionWidth() / 2, RenderMan::getRenderPars().resolutionHeight() / 2);
	}

  Position2I Screen::getClientTopLeft()
  {
    return Position2I(0, 0);
  }

  Position2I Screen::getClientRightBottom()
  {
    return Position2I(RenderMan::getRenderPars().resolutionWidth(), RenderMan::getRenderPars().resolutionHeight());
  }


} // ns Doh3d
