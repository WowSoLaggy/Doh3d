#pragma once

#ifndef INC_DOH3D_WINCLASS_H
#define INC_DOH3D_WINCLASS_H


#include "StartupPars.h"


namespace Doh3d
{

	class WinClass
	{
	public:

		static const StartupPars& GetStartupPars() { return m_startupPars; }
		static const std::string& GetApplicationName() { return m_applicationName; }

		static void Register(const StartupPars& pStartupPars, const std::string& pApplicationName);
		static void Unregister();

	private:

		static StartupPars m_startupPars;
		static std::string m_applicationName;

		static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	};

} // ns Doh3d


#endif // INC_DOH3D_WINCLASS_H
