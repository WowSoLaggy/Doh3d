#include "Doh3d.h"
#include "InputMan.h"

#include "RenderMan.h"
#include "Screen.h"


namespace Doh3d
{

	volatile bool InputMan::m_isCreated;
	InputPars InputMan::m_inputPars;
	D3DXVECTOR2 InputMan::m_cursorPosition;

	LPDIRECTINPUT8 InputMan::m_directInput;
	LPDIRECTINPUTDEVICE8 InputMan::m_mouse;
	LPDIRECTINPUTDEVICE8 InputMan::m_keyboard;

	char InputMan::m_keysPrev[256];
	char InputMan::m_keys[256];
	DIMOUSESTATE InputMan::m_mouseState;
	DIMOUSESTATE InputMan::m_mouseStatePrev;


	ErrCode3d InputMan::Init()
	{
		m_isCreated = false;

		return err3d_noErr;
	}

	ErrCode3d InputMan::Dispose()
	{
		LOG("InputMan::Dispose()");
		ErrCode3d err3d;

		m_isCreated = false;

		err3d = DisposeInputDevices();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't dispose InputDevices.");
			return err3d;
		}

		return err3d_noErr;
	}


	ErrCode3d InputMan::Recreate(const InputPars& pInputPars)
	{
		LOG("InputMan::Recreate()");
		ErrCode3d err3d;

		m_inputPars = pInputPars;

		err3d = Dispose();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't dispose InputDevice.");
			return err3d;
		}

		err3d = CreateInputDevices();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't create InputDevice.");
			return err3d;
		}

		m_isCreated = true;
		return err3d_noErr;
	}

	ErrCode3d InputMan::CheckDevices()
	{
		LOG("InputMan::CheckDevices()");
		ErrCode3d err3d;
		HRESULT hRes = 0;

		// Mouse

		memcpy(&m_mouseStatePrev, &m_mouseState, sizeof(m_mouseStatePrev));

		hRes = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState);
		if (hRes != DI_OK)
		{
			err3d = AcquireMouse();
			if (err3d != err3d_noErr)
			{
				echo("ERROR: Can't acquire mouse InputDevice.");
				return err3d;
			}
		}

		m_cursorPosition.x += (int)(m_mouseState.lX * m_inputPars.MouseSensX);
		m_cursorPosition.y += (int)(m_mouseState.lY * m_inputPars.MouseSensY);

		m_cursorPosition.x = m_cursorPosition.x < 0 ? 0 : m_cursorPosition.x > Screen::GetClientWidth() - 1 ? Screen::GetClientWidth() - 1 : m_cursorPosition.x;
		m_cursorPosition.y = m_cursorPosition.y < 0 ? 0 : m_cursorPosition.y > Screen::GetClientHeight() - 1 ? Screen::GetClientHeight() - 1 : m_cursorPosition.y;

		// Mouse move

		if ((m_mouseState.lX != 0) || (m_mouseState.lY != 0))
		{
			if (m_inputPars.OnMouseMove != nullptr)
				m_inputPars.OnMouseMove();
		}

		// Mouse buttons

		for (int i = MBUTTON_LEFT; i <= MBUTTON_RIGHT; ++i)
		{
			if ((m_mouseState.rgbButtons[i] & 0x80) && !(m_mouseStatePrev.rgbButtons[i] & 0x80))
			{
				if (m_inputPars.OnMouseDown != nullptr)
					m_inputPars.OnMouseDown(i);
			}
			else if (!(m_mouseState.rgbButtons[i] & 0x80) && (m_mouseStatePrev.rgbButtons[i] & 0x80))
			{
				if (m_inputPars.OnMouseUp != nullptr)
					m_inputPars.OnMouseUp(i);
			}
		}

		// Keyboard

		memcpy(m_keysPrev, m_keys, sizeof(m_keys));

		hRes = m_keyboard->GetDeviceState(sizeof(m_keys), m_keys);
		if (hRes != DI_OK)
			AcquireKeyboard();

		for (int i = 0; i < KBUTTONS_MAX; ++i)
		{
			if ((m_keys[i] & 0x80) != 0)
			{
				if ((m_keysPrev[i] & 0x80) == 0)
				{
					if (m_inputPars.OnKeyDown != nullptr)
						m_inputPars.OnKeyDown(i);
				}

				if (m_inputPars.OnKeyPressed != nullptr)
					m_inputPars.OnKeyPressed(i);
			}
			else
			{
				if ((m_keysPrev[i] & 0x80) != 0)
				{
					if (m_inputPars.OnKeyUp != nullptr)
						m_inputPars.OnKeyUp(i);
				}
			}
		}

		return err3d_noErr;
	}


	ErrCode3d InputMan::CreateInputDevices()
	{
		LOG("InputMan::CreateInputDevices()");
		ErrCode3d err3d;
		int res = 0;

		res = DirectInput8Create(WinClass::GetStartupPars().hInstance, DIRECTINPUT_VERSION,
								 IID_IDirectInput8, (void **)&m_directInput, NULL);
		if ((res != DI_OK) || (m_directInput == nullptr))
		{
			echo("ERROR: Can't create DirectInput.");
			return err3d_cantCreateDirectInput;
		}

		res = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if ((res != DI_OK) || (m_mouse == nullptr))
		{
			echo("ERROR: Cat't create mouse InputDevice");
			return err3d_cantCreateInputDevice;
		}

		m_mouse->SetDataFormat(&c_dfDIMouse);
		m_mouse->SetCooperativeLevel(RenderMan::GetHWindow(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);

		err3d = AcquireMouse();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't acquire mouse device.");
			return err3d;
		}

		res = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
		if ((res != DI_OK) || (m_keyboard == nullptr))
		{
			echo("ERROR: Can't create keyboard InputDevice.");
			return err3d_cantCreateInputDevice;
		}

		m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		m_keyboard->SetCooperativeLevel(RenderMan::GetHWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		err3d = AcquireKeyboard();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't acquire mouse device.");
			return err3d;
		}

		m_cursorPosition = Screen::GetClientCenter();

		return err3d_noErr;
	}

	ErrCode3d InputMan::DisposeInputDevices()
	{
		if (m_mouse != nullptr)
		{
			m_mouse->Unacquire();
			m_mouse->Release();
			m_mouse = nullptr;
		}

		if (m_keyboard != nullptr)
		{
			m_keyboard->Unacquire();
			m_keyboard->Release();
			m_keyboard = nullptr;
		}

		if (m_directInput != nullptr)
		{
			m_directInput->Release();
			m_directInput = nullptr;
		}

		return err3d_noErr;
	}

	ErrCode3d InputMan::AcquireMouse()
	{
		m_mouse->Acquire();
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));
		ZeroMemory(&m_mouseStatePrev, sizeof(m_mouseStatePrev));

		return err3d_noErr;
	}

	ErrCode3d InputMan::AcquireKeyboard()
	{
		m_keyboard->Acquire();
		ZeroMemory(m_keys, sizeof(m_keys));

		return err3d_noErr;
	}


	bool InputMan::IsShift()
	{
		return ((m_keys[DIK_LSHIFT] & 0x80) || (m_keys[DIK_RSHIFT] & 0x80));
	}

	bool InputMan::IsCtrl()
	{
		return ((m_keys[DIK_LCONTROL] & 0x80) || (m_keys[DIK_RCONTROL] & 0x80));
	}

	bool InputMan::IsAlt()
	{
		return ((m_keys[DIK_LALT] & 0x80) || (m_keys[DIK_RALT] & 0x80));
	}

} // Doh3d
