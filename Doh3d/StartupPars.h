#pragma once


namespace Doh3d
{

	struct StartupPars
	{

    StartupPars()
      : hInstance(nullptr), hPrevInstance(nullptr), lpCmdLine(nullptr), nCmdShow(0) { }

		StartupPars(HINSTANCE pHInstance, HINSTANCE pHPrevInstance, LPSTR pLpCmdLine, int pNCmdShow)
			: hInstance(pHInstance), hPrevInstance(pHPrevInstance), lpCmdLine(pLpCmdLine), nCmdShow(pNCmdShow) { }

		HINSTANCE hInstance;			// Win32 application entry point parameters
		HINSTANCE hPrevInstance;  //
		LPSTR lpCmdLine;				  //
		int nCmdShow;					    //

	};

} // ns Doh3d
