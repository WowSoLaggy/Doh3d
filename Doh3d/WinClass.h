#pragma once

#ifndef INC_DOH3D_WINCLASS_H
#define INC_DOH3D_WINCLASS_H


#include "StartupPars.h"


namespace Doh3d
{

	class WinClass
	{
	public:

		const StartupPars& GetStartupPars() { return m_startupPars; }
		const std::string& GetApplicationName() { return m_applicationName; }

		void Register(const StartupPars& pStartupPars, const std::string& pApplicationName);
		void Unregister();

	private:

		StartupPars m_startupPars;
		std::string m_applicationName;

		static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	};

} // ns Doh3d


#endif // INC_DOH3D_WINCLASS_H
