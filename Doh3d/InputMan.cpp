#include "PrecompiledHeader.h"
#include "InputMan.h"

#include "RenderMan.h"
#include "Screen.h"


namespace Doh3d
{

	volatile bool InputMan::d_isCreated;
	InputPars InputMan::d_inputPars;
	D3DXVECTOR2 InputMan::d_cursorPosition;

	LPDIRECTINPUT8 InputMan::d_directInput;
	LPDIRECTINPUTDEVICE8 InputMan::d_mouse;
	LPDIRECTINPUTDEVICE8 InputMan::d_keyboard;

	char InputMan::d_keysPrev[256];
	char InputMan::d_keys[256];
	DIMOUSESTATE InputMan::d_mouseState;
	DIMOUSESTATE InputMan::d_mouseStatePrev;


  bool InputMan::init()
	{
		d_isCreated = false;
		return true;
	}

  bool InputMan::dispose()
	{
		LOG("InputMan::dispose()");

		d_isCreated = false;

		if (!disposeInputDevices())
		{
			echo("ERROR: Can't dispose InputDevices.");
			return false;
		}

		return true;
	}


  bool InputMan::recreate(const InputPars& pInputPars)
	{
		LOG("InputMan::recreate()");

		d_inputPars = pInputPars;

		if (!dispose())
		{
			echo("ERROR: Can't dispose InputDevice.");
			return false;
		}

		if (!createInputDevices())
		{
			echo("ERROR: Can't create InputDevice.");
			return false;
		}

		d_isCreated = true;
		return true;
	}

  bool InputMan::checkDevices()
	{
		LOG("InputMan::checkDevices()");
		HRESULT hRes = 0;

		// Mouse

		memcpy(&d_mouseStatePrev, &d_mouseState, sizeof(d_mouseStatePrev));

		hRes = d_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &d_mouseState);
		if (hRes != DI_OK)
		{
			if (!acquireMouse())
			{
				echo("ERROR: Can't acquire mouse InputDevice.");
				return false;
			}
		}

		d_cursorPosition.x += (int)(d_mouseState.lX * d_inputPars.mouseSensX());
		d_cursorPosition.y += (int)(d_mouseState.lY * d_inputPars.mouseSensY());

		d_cursorPosition.x = d_cursorPosition.x < 0 ? 0 : d_cursorPosition.x > Screen::getClientWidth() - 1 ? Screen::getClientWidth() - 1 : d_cursorPosition.x;
		d_cursorPosition.y = d_cursorPosition.y < 0 ? 0 : d_cursorPosition.y > Screen::getClientHeight() - 1 ? Screen::getClientHeight() - 1 : d_cursorPosition.y;

		// Mouse move

		if ((d_mouseState.lX != 0) || (d_mouseState.lY != 0))
		{
			if (d_inputPars.onMouseMove() != nullptr)
				d_inputPars.onMouseMove()();
		}

		// Mouse buttons

		for (int i = MBUTTON_LEFT; i <= MBUTTON_RIGHT; ++i)
		{
			if ((d_mouseState.rgbButtons[i] & KEY_PRESSED_FLAG) && !(d_mouseStatePrev.rgbButtons[i] & KEY_PRESSED_FLAG))
			{
				if (d_inputPars.onMouseDown() != nullptr)
					d_inputPars.onMouseDown()(i);
			}
			else if (!(d_mouseState.rgbButtons[i] & KEY_PRESSED_FLAG) && (d_mouseStatePrev.rgbButtons[i] & KEY_PRESSED_FLAG))
			{
				if (d_inputPars.onMouseUp() != nullptr)
					d_inputPars.onMouseUp()(i);
			}
		}

		// Keyboard

		memcpy(d_keysPrev, d_keys, sizeof(d_keys));

		hRes = d_keyboard->GetDeviceState(sizeof(d_keys), d_keys);
		if (hRes != DI_OK)
			acquireKeyboard();

		for (int i = 0; i < KBUTTONS_MAX; ++i)
		{
			if ((d_keys[i] & KEY_PRESSED_FLAG) != 0)
			{
				if ((d_keysPrev[i] & KEY_PRESSED_FLAG) == 0)
				{
					if (d_inputPars.onKeyDown() != nullptr)
						d_inputPars.onKeyDown()(i);
				}

				if (d_inputPars.onKeyPressed() != nullptr)
					d_inputPars.onKeyPressed()(i);
			}
			else
			{
				if ((d_keysPrev[i] & KEY_PRESSED_FLAG) != 0)
				{
					if (d_inputPars.onKeyUp() != nullptr)
						d_inputPars.onKeyUp()(i);
				}
			}
		}

		return true;
	}


  bool InputMan::createInputDevices()
	{
		LOG("InputMan::createInputDevices()");
		int res = 0;

		res = DirectInput8Create(WinClass::startupPars().hInstance, DIRECTINPUT_VERSION,
								 IID_IDirectInput8, (void **)&d_directInput, NULL);
		if ((res != DI_OK) || (d_directInput == nullptr))
		{
			echo("ERROR: Can't create DirectInput.");
			return false;
		}

		res = d_directInput->CreateDevice(GUID_SysMouse, &d_mouse, NULL);
		if ((res != DI_OK) || (d_mouse == nullptr))
		{
			echo("ERROR: Cat't create mouse InputDevice");
			return false;
		}

		d_mouse->SetDataFormat(&c_dfDIMouse);
		d_mouse->SetCooperativeLevel(RenderMan::getHWindow(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);

		if (!acquireMouse())
		{
			echo("ERROR: Can't acquire mouse device.");
			return false;
		}

		res = d_directInput->CreateDevice(GUID_SysKeyboard, &d_keyboard, NULL);
		if ((res != DI_OK) || (d_keyboard == nullptr))
		{
			echo("ERROR: Can't create keyboard InputDevice.");
			return false;
		}

		d_keyboard->SetDataFormat(&c_dfDIKeyboard);
		d_keyboard->SetCooperativeLevel(RenderMan::getHWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		if (!acquireKeyboard())
		{
			echo("ERROR: Can't acquire mouse device.");
			return false;
		}

		d_cursorPosition = Screen::getClientCenter();

		return true;
	}

  bool InputMan::disposeInputDevices()
	{
		if (d_mouse != nullptr)
		{
			d_mouse->Unacquire();
			d_mouse->Release();
			d_mouse = nullptr;
		}

		if (d_keyboard != nullptr)
		{
			d_keyboard->Unacquire();
			d_keyboard->Release();
			d_keyboard = nullptr;
		}

		if (d_directInput != nullptr)
		{
			d_directInput->Release();
			d_directInput = nullptr;
		}

		return true;
	}

  bool InputMan::acquireMouse()
	{
		d_mouse->Acquire();
		ZeroMemory(&d_mouseState, sizeof(d_mouseState));
		ZeroMemory(&d_mouseStatePrev, sizeof(d_mouseStatePrev));

		return true;
	}

  bool InputMan::acquireKeyboard()
	{
		d_keyboard->Acquire();
		ZeroMemory(d_keys, sizeof(d_keys));

		return true;
	}


	bool InputMan::isShift()
	{
		return ((d_keys[DIK_LSHIFT] & KEY_PRESSED_FLAG) || (d_keys[DIK_RSHIFT] & KEY_PRESSED_FLAG));
	}

	bool InputMan::isCtrl()
	{
		return ((d_keys[DIK_LCONTROL] & KEY_PRESSED_FLAG) || (d_keys[DIK_RCONTROL] & KEY_PRESSED_FLAG));
	}

	bool InputMan::isAlt()
	{
		return ((d_keys[DIK_LALT] & KEY_PRESSED_FLAG) || (d_keys[DIK_RALT] & KEY_PRESSED_FLAG));
	}

} // Doh3d
