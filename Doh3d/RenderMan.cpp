#include "Doh3d.h"
#include "RenderMan.h"

#include "WinClass.h"
#include "Screen.h"


namespace Doh3d
{

	bool RenderMan::m_isCreated = false;
	RenderPars RenderMan::m_renderPars;

	HWND RenderMan::m_hWindow;
	LPDIRECT3D9 RenderMan::m_direct3d;
	D3DPRESENT_PARAMETERS RenderMan::m_presentPars;
	D3DCAPS9 RenderMan::m_caps;
	LPDIRECT3DDEVICE9 RenderMan::m_renderDevice;
	LPDIRECT3DSURFACE9 RenderMan::m_defaultRenderTarget;
	D3DSURFACE_DESC RenderMan::m_defaultRenderTargetDesc;


  bool RenderMan::Recreate(const WinClass& pWinClass, const RenderPars& pRenderPars)
	{
		LOG("RenderMan::Recreate()");

		m_renderPars = pRenderPars;

		if (!Dispose())
		{
			echo("ERROR: Can't dispose RenderMan.");
			return false;
		}

		if (!CreateWnd(pWinClass))
		{
			echo("ERROR: Can't create Wnd.");
			return false;
		}

		if (!CreateRenderDevice())
		{
			echo("ERROR: Can't create RenderDevice.");
			return false;
		}

		m_isCreated = true;
		return true;
	}


  bool RenderMan::Dispose()
	{
		LOG("RenderMan::Dispose()");

		m_isCreated = false;

		if (!DisposeRenderDevice())
		{
			echo("ERROR: Can't dispose RenderDevice.");
			return false;
		}

		if (!DisposeWnd())
		{
			echo("ERROR: Can't dispose Wnd.");
			return false;
		}

		return true;
	}


  bool RenderMan::CreateWnd(const WinClass& pWinClass)
	{
		LOG("RDManager::CreateWnd()");

		// Create window

		DWORD dwStyle = WS_VISIBLE | WS_POPUP;
		if (m_renderPars.WndCaption)
			dwStyle |= WS_CAPTION | WS_SYSMENU;

		m_hWindow = CreateWindowEx(0, pWinClass.applicationName().c_str(), pWinClass.applicationName().c_str(), dwStyle,
								   (Screen::GetDesktopWidth() - m_renderPars.ResolutionWidth) / 2, (Screen::GetDesktopHeight() - m_renderPars.ResolutionHeight) / 2,
								   m_renderPars.ResolutionWidth, m_renderPars.ResolutionHeight,
								   nullptr, nullptr, pWinClass.startupPars().hInstance, nullptr);
		if (m_hWindow == nullptr)
		{
			echo("ERROR: Can't create window.");
			return false;
		}

		ShowWindow(m_hWindow, pWinClass.startupPars().nCmdShow);
		UpdateWindow(m_hWindow);

		return true;
	}

  bool RenderMan::DisposeWnd()
	{
		if (m_hWindow != nullptr)
		{
			DestroyWindow(m_hWindow);
			m_hWindow = nullptr;
		}

		return true;
	}


  bool RenderMan::CreateRenderDevice()
	{
		LOG("RenderMan::CreateRenderDevice()");
		int res = 0;

		m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (m_direct3d == nullptr)
		{
			echo("ERROR: Can't create Direct3D.");
			return false;
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
			return false;
		}

		m_renderDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_renderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_renderDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_renderDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_renderDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_renderDevice->GetRenderTarget(0, &m_defaultRenderTarget);
		m_defaultRenderTarget->GetDesc(&m_defaultRenderTargetDesc);

		return true;
	}

  bool RenderMan::DisposeRenderDevice()
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

		return true;
	}


} // ns Doh3d
