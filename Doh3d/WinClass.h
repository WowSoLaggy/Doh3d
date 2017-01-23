#pragma once

#ifndef INC_DOH3D_WINCLASS_H
#define INC_DOH3D_WINCLASS_H


#include "StartupPars.h"


namespace Doh3d
{

	class WinClass
	{
	public:

		const StartupPars& startupPars() const { return d_startupPars; }
		const std::string& applicationName() const { return d_applicationName; }

		void registerClass(const StartupPars& pStartupPars, const std::string& pApplicationName);
		void unregisterClass();

	private:

		StartupPars d_startupPars;
		std::string d_applicationName;

		static LRESULT __stdcall wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	};

} // ns Doh3d


#endif // INC_DOH3D_WINCLASS_H
