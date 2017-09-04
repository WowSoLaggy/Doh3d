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

		static bool isCreated() { return d_isCreated; }
		static Position2 getCursorPosition() { return d_cursorPosition; }

		static bool init();
		static bool dispose();

		static bool recreate(const InputPars& pInputPars);
		static bool checkDevices();

		static bool isShift();
		static bool isCtrl();
		static bool isAlt();

		static char dikToChar(int pDik);
		static bool isPrintable(int pDik);

	private:

    static const char KEY_PRESSED_FLAG = (char)0x80;

		static volatile bool d_isCreated;
		static InputPars d_inputPars;
		static Position2 d_cursorPosition;

		static LPDIRECTINPUT8 d_directInput;
		static LPDIRECTINPUTDEVICE8 d_mouse;
		static LPDIRECTINPUTDEVICE8 d_keyboard;

		static char d_keysPrev[256];
		static char d_keys[256];
		static DIMOUSESTATE d_mouseState;
		static DIMOUSESTATE d_mouseStatePrev;

		static bool createInputDevices();
		static bool disposeInputDevices();
		static bool acquireMouse();
		static bool acquireKeyboard();

		static char dikToChar(int pDik, bool pShift);

	};

} // ns Doh3d


#endif // INC_DOH3D_INPUTMAN_H
