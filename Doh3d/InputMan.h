#pragma once

#ifndef INC_DOH3D_INPUTMAN_H
#define INC_DOH3D_INPUTMAN_H


#include "InputPars.h"
#include "WinClass.h"


namespace Doh3d
{

#define MBUTTON_LEFT	0
#define MBUTTON_RIGHT	1
#define KBUTTONS_MAX	256
#define CHARSCOUNT 145


	class InputMan
	{
	public:

		static bool IsCreated() { return m_isCreated; }
		static D3DXVECTOR2 GetCursorPosition() { return m_cursorPosition; }

		static bool Init();
		static bool Dispose();

		static bool Recreate(const WinClass& pWinClass, const InputPars& pInputPars);
		static bool CheckDevices();

		static bool IsShift();
		static bool IsCtrl();
		static bool IsAlt();

		static char DikToChar(int pDik);
		static bool IsPrintable(int pDik);

	private:

		static volatile bool m_isCreated;
		static InputPars m_inputPars;
		static D3DXVECTOR2 m_cursorPosition;

		static LPDIRECTINPUT8 m_directInput;
		static LPDIRECTINPUTDEVICE8 m_mouse;
		static LPDIRECTINPUTDEVICE8 m_keyboard;

		static char m_keysPrev[256];
		static char m_keys[256];
		static DIMOUSESTATE m_mouseState;
		static DIMOUSESTATE m_mouseStatePrev;

		static bool CreateInputDevices(const WinClass& pWinClass);
		static bool DisposeInputDevices();
		static bool AcquireMouse();
		static bool AcquireKeyboard();

		static char DikToChar(int pDik, bool pShift);

	};

} // ns Doh3d


#endif // INC_DOH3D_INPUTMAN_H
