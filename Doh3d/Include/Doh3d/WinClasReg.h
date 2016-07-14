#pragma once

#ifndef WINCLASSREG_H
#define WINCLASSREG_H


#include "StartupPars.h"


namespace Doh3d
{

	void WinClassReg(StartupPars &pStartupPars);

	void WinClassUnreg(StartupPars &pStartupPars);

	LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

} // ns Doh3d


#endif // WINCLASSREG_H
