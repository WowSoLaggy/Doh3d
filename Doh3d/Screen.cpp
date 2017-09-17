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
		return Position2I(getClientCenterX(), getClientCenterY());
	}

  int Screen::getClientCenterX()
  {
    return getClientWidth() / 2;
  }

  int Screen::getClientCenterY()
  {
    return getClientHeight() / 2;
  }


  Position2I Screen::getClientTopLeft()
  {
    return Position2I(0, 0);
  }

  Position2I Screen::getClientRightBottom()
  {
    return Position2I(getClientWidth(), getClientHeight());
  }


} // ns Doh3d
