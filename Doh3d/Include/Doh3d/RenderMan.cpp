#include "..\Doh3d.h"
#include "RenderMan.h"


namespace Doh3d
{

	bool RenderMan::m_isCreated = false;

	HWND RenderMan::m_hWindow;
	IDirect3D9 *RenderMan::m_direct3d;
	D3DPRESENT_PARAMETERS RenderMan::m_presentPars;
	D3DCAPS9 RenderMan::m_caps;
	IDirect3DDevice9 *RenderMan::m_renderDevice;
	LPDIRECT3DSURFACE9 RenderMan::m_defaultRenderTarget;
	D3DSURFACE_DESC RenderMan::m_defaultRenderTargetDesc;


	ErrCode RenderMan::Recreate(RenderPars &pRenderPars, StartupPars &pStartupPars)
	{
		LOG("RenderMan::Recreate()");
		ErrCode err;

		err = Dispose();
		if (err != err_noErr)
		{
			echo("ERROR: Can't Dispose RenderMan.");
			return err;
		}

		err = CreateWnd(pRenderPars, pStartupPars);
		if (err != err_noErr)
		{
			echo("ERROR: Can't create Wnd.");
			return err;
		}

		err = CreateRenderDevice(pRenderPars);
		if (err != err_noErr)
		{
			echo("ERROR: Can't create RenderDevice.");
			return err;
		}

		m_isCreated = true;
		return err_noErr;
	}


	ErrCode RenderMan::Dispose()
	{
		LOG("RenderMan::Dispose()");
		ErrCode err;

		m_isCreated = false;

		err = DisposeRenderDevice();
		if (err != err_noErr)
		{
			echo("ERROR: Can't dispose RenderDevice.");
			return err;
		}

		err = DisposeWnd();
		if (err != err_noErr)
		{
			echo("ERROR: Can't dispose Wnd.");
			return err;
		}

		return err_noErr;
	}


	ErrCode RenderMan::CreateWnd(RenderPars &pRenderPars, StartupPars &pStartupPars)
	{
		LOG("RDManager::CreateWnd()");

		// Get screen size

		RECT rectDesktop;
		HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &rectDesktop);
		LONG m_screenWidth = rectDesktop.right - rectDesktop.left;
		LONG m_screenHeight = rectDesktop.bottom - rectDesktop.top;

		// Create window

		DWORD dwStyle = WS_VISIBLE | WS_POPUP;
		if (pRenderPars.WndCaption)
			dwStyle |= WS_CAPTION;

		m_hWindow = CreateWindowEx(0, pStartupPars.ApplicationName.c_str(), pStartupPars.ApplicationName.c_str(), dwStyle,
			(m_screenWidth - pRenderPars.ResolutionWidth) / 2, (m_screenHeight - pRenderPars.ResolutionHeight) / 2,
			pRenderPars.ResolutionWidth, pRenderPars.ResolutionHeight,
			nullptr, nullptr, pStartupPars.hInstance, nullptr);
		if (m_hWindow == nullptr)
		{
			echo("ERROR: Can't create window.");
			return err_cantCreateWindow;
		}

		ShowWindow(m_hWindow, pStartupPars.nCmdShow);
		UpdateWindow(m_hWindow);

		return err_noErr;
	}

	ErrCode RenderMan::DisposeWnd()
	{
		if (m_hWindow != nullptr)
		{
			DestroyWindow(m_hWindow);
			m_hWindow = nullptr;
		}

		return err_noErr;
	}


	ErrCode RenderMan::CreateRenderDevice(RenderPars &pRenderPars)
	{
		LOG("RenderMan::CreateRenderDevice()");
		int res = 0;

		m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (m_direct3d == nullptr)
		{
			echo("ERROR: Can't create Direct3D.");
			return err_cantCreateDirectX;
		}

		m_direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_caps);

		ZeroMemory(&m_presentPars, sizeof(m_presentPars));
		m_presentPars.EnableAutoDepthStencil = true;
		m_presentPars.AutoDepthStencilFormat = D3DFMT_D24X8;
		m_presentPars.BackBufferWidth = pRenderPars.ResolutionWidth;
		m_presentPars.BackBufferHeight = pRenderPars.ResolutionHeight;
		m_presentPars.BackBufferFormat = D3DFMT_A8R8G8B8;
		m_presentPars.BackBufferCount = 1;
		m_presentPars.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//m_presentPars.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_presentPars.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		m_presentPars.hDeviceWindow = m_hWindow;
		m_presentPars.Windowed = pRenderPars.Windowed;
		if (!pRenderPars.Windowed)
			m_presentPars.FullScreen_RefreshRateInHz = pRenderPars.FullScreenRefreshRate;

		res = m_direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWindow,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
			&m_presentPars, &m_renderDevice);
		if ((res != D3D_OK) || (m_renderDevice == nullptr))
		{
			echo("ERROR: Can't create RenderDevice.");
			return err_cantCreateRenderDevice;
		}

		m_renderDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_renderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_renderDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_renderDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_renderDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_renderDevice->GetRenderTarget(0, &m_defaultRenderTarget);
		m_defaultRenderTarget->GetDesc(&m_defaultRenderTargetDesc);

		return err_noErr;
	}

	ErrCode RenderMan::DisposeRenderDevice()
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

		return err_noErr;
	}


} // ns Doh3d
