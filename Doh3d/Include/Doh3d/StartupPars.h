#pragma once

#ifndef STARTUPPARS_H
#define STARTUPPARS_H


namespace Doh3d
{

	struct StartupPars
	{

		StartupPars()
			: hInstance(nullptr), hPrevInstance(nullptr), lpCmdLine(nullptr), nCmdShow(0), ApplicationName("") { }

		StartupPars(HINSTANCE &pHInstance, HINSTANCE &pHPrevInstance, LPSTR &pLpCmdLine, int &pNCmdShow, std::string pApplicationName)
			: hInstance(pHInstance), hPrevInstance(pHPrevInstance), lpCmdLine(pLpCmdLine), nCmdShow(pNCmdShow), ApplicationName(pApplicationName) { }

		HINSTANCE hInstance;			// Win32 application entry point parameters
		HINSTANCE hPrevInstance;		//
		LPSTR lpCmdLine;				//
		int nCmdShow;					//
		std::string ApplicationName;	// Name of the application

	};

} // ns Doh3d


#endif // STARTUPPARS_H
