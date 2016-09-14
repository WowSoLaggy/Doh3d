#include "..\Doh3d.h"
#include "RenderMan.h"

#include "WinClass.h"
#include "Screen.h"


namespace Doh3d
{

	bool RenderMan::m_isCreated = false;
	RenderPars RenderMan::m_renderPars;

	HWND RenderMan::m_hWindow;
	IDirect3D9 *RenderMan::m_direct3d;
	D3DPRESENT_PARAMETERS RenderMan::m_presentPars;
	D3DCAPS9 RenderMan::m_caps;
	IDirect3DDevice9 *RenderMan::m_renderDevice;
	LPDIRECT3DSURFACE9 RenderMan::m_defaultRenderTarget;
	D3DSURFACE_DESC RenderMan::m_defaultRenderTargetDesc;


	ErrCode3d RenderMan::Recreate(const RenderPars &pRenderPars)
	{
		LOG("RenderMan::Recreate()");
		ErrCode3d err;

		m_renderPars = pRenderPars;

		err = Dispose();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't Dispose RenderMan.");
			return err;
		}

		err = CreateWnd(WinClass::GetStartupPars());
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't create Wnd.");
			return err;
		}

		err = CreateRenderDevice();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't create RenderDevice.");
			return err;
		}

		m_isCreated = true;
		return err3d_noErr;
	}


	ErrCode3d RenderMan::Dispose()
	{
		LOG("RenderMan::Dispose()");
		ErrCode3d err;

		m_isCreated = false;

		err = DisposeRenderDevice();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't dispose RenderDevice.");
			return err;
		}

		err = DisposeWnd();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't dispose Wnd.");
			return err;
		}

		return err3d_noErr;
	}


	ErrCode3d RenderMan::CreateWnd(const StartupPars &pStartupPars)
	{
		LOG("RDManager::CreateWnd()");

		// Create window

		DWORD dwStyle = WS_VISIBLE | WS_POPUP;
		if (m_renderPars.WndCaption)
			dwStyle |= WS_CAPTION | WS_SYSMENU;

		m_hWindow = CreateWindowEx(0, WinClass::GetApplicationName().c_str(), WinClass::GetApplicationName().c_str(), dwStyle,
								   (Screen::GetDesktopWidth() - m_renderPars.ResolutionWidth) / 2, (Screen::GetDesktopHeight() - m_renderPars.ResolutionHeight) / 2,
								   m_renderPars.ResolutionWidth, m_renderPars.ResolutionHeight,
								   nullptr, nullptr, pStartupPars.hInstance, nullptr);
		if (m_hWindow == nullptr)
		{
			echo("ERROR: Can't create window.");
			return err3d_cantCreateWindow;
		}

		ShowWindow(m_hWindow, pStartupPars.nCmdShow);
		UpdateWindow(m_hWindow);

		return err3d_noErr;
	}

	ErrCode3d RenderMan::DisposeWnd()
	{
		if (m_hWindow != nullptr)
		{
			DestroyWindow(m_hWindow);
			m_hWindow = nullptr;
		}

		return err3d_noErr;
	}


	ErrCode3d RenderMan::CreateRenderDevice()
	{
		LOG("RenderMan::CreateRenderDevice()");
		int res = 0;

		m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (m_direct3d == nullptr)
		{
			echo("ERROR: Can't create Direct3D.");
			return err3d_cantCreateDirectX;
		}

		m_direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_caps);

		ZeroMemory(&m_presentPars, sizeof(m_presentPars));
		m_presentPars.EnableAutoDepthStencil = true;
		m_presentPars.AutoDepthStencilFormat = D3DFMT_D24X8;
		m_presentPars.BackBufferWidth = m_renderPars.ResolutionWidth;
		m_presentPars.BackBufferHeight = m_renderPars.ResolutionHeight;
		m_presentPars.BackBufferFormat = D3DFMT_A8R8G8B8;
		m_presentPars.BackBufferCount = 1;
		m_presentPars.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//m_presentPars.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_presentPars.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		m_presentPars.hDeviceWindow = m_hWindow;
		m_presentPars.Windowed = m_renderPars.Windowed;
		if (!m_renderPars.Windowed)
			m_presentPars.FullScreen_RefreshRateInHz = m_renderPars.FullScreenRefreshRate;

		res = m_direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWindow,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
			&m_presentPars, &m_renderDevice);
		if ((res != D3D_OK) || (m_renderDevice == nullptr))
		{
			echo("ERROR: Can't create RenderDevice.");
			return err3d_cantCreateRenderDevice;
		}

		m_renderDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_renderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_renderDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_renderDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_renderDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_renderDevice->GetRenderTarget(0, &m_defaultRenderTarget);
		m_defaultRenderTarget->GetDesc(&m_defaultRenderTargetDesc);

		return err3d_noErr;
	}

	ErrCode3d RenderMan::DisposeRenderDevice()
	{
		if (m_renderDevice != nullptr)
		{
			m_renderDevice->Release();
			m_renderDevice = nullptr;
		}

		if (m_direct3d != nullptr)
		{
			m_direct3d->Release();
			m_direct3d = nullptr;
		}

		return err3d_noErr;
	}


} // ns Doh3d
