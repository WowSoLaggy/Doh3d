#include "Doh3d.h"
#include "RenderMan.h"

#include "WinClass.h"
#include "Screen.h"


namespace Doh3d
{

	bool RenderMan::d_isCreated = false;
	RenderPars RenderMan::d_renderPars;

	HWND RenderMan::d_hWindow;
	LPDIRECT3D9 RenderMan::d_direct3d;
	D3DPRESENT_PARAMETERS RenderMan::d_presentPars;
	D3DCAPS9 RenderMan::d_caps;
	LPDIRECT3DDEVICE9 RenderMan::d_renderDevice;
	LPDIRECT3DSURFACE9 RenderMan::d_defaultRenderTarget;
	D3DSURFACE_DESC RenderMan::d_defaultRenderTargetDesc;


  bool RenderMan::recreate(const RenderPars& pRenderPars, const std::string& pWindowCaption)
	{
		LOG("RenderMan::recreate()");

		d_renderPars = pRenderPars;

		if (!dispose())
		{
			echo("ERROR: Can't dispose RenderMan.");
			return false;
		}

		if (!createWnd(pWindowCaption))
		{
			echo("ERROR: Can't create Wnd.");
			return false;
		}

		if (!createRenderDevice())
		{
			echo("ERROR: Can't create RenderDevice.");
			return false;
		}

		d_isCreated = true;
		return true;
	}


  bool RenderMan::dispose()
	{
		LOG("RenderMan::dispose()");

		d_isCreated = false;

		if (!disposeRenderDevice())
		{
			echo("ERROR: Can't dispose RenderDevice.");
			return false;
		}

		if (!disposeWnd())
		{
			echo("ERROR: Can't dispose Wnd.");
			return false;
		}

		return true;
	}


  bool RenderMan::createWnd(const std::string& pWindowCaption)
	{
		LOG("RDManager::createWnd()");

		// Create window

		DWORD dwStyle = WS_VISIBLE | WS_POPUP;
		if (d_renderPars.hasBorder())
			dwStyle |= WS_CAPTION | WS_SYSMENU;

		d_hWindow = CreateWindowEx(0, pWindowCaption.c_str(), pWindowCaption.c_str(), dwStyle,
								   (Screen::getDesktopWidth() - d_renderPars.resolutionWidth()) / 2, (Screen::getDesktopHeight() - d_renderPars.resolutionHeight()) / 2,
								   d_renderPars.resolutionWidth(), d_renderPars.resolutionHeight(),
								   nullptr, nullptr, WinClass::startupPars().hInstance, nullptr);
		if (d_hWindow == nullptr)
		{
			echo("ERROR: Can't create window.");
			return false;
		}

		ShowWindow(d_hWindow, WinClass::startupPars().nCmdShow);
		UpdateWindow(d_hWindow);

		return true;
	}

  bool RenderMan::disposeWnd()
	{
		if (d_hWindow != nullptr)
		{
			DestroyWindow(d_hWindow);
			d_hWindow = nullptr;
		}

		return true;
	}


  bool RenderMan::createRenderDevice()
	{
		LOG("RenderMan::createRenderDevice()");
		int res = 0;

		d_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (d_direct3d == nullptr)
		{
			echo("ERROR: Can't create Direct3D.");
			return false;
		}

		d_direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d_caps);

		ZeroMemory(&d_presentPars, sizeof(d_presentPars));
		d_presentPars.EnableAutoDepthStencil = true;
		d_presentPars.AutoDepthStencilFormat = D3DFMT_D24X8;
		d_presentPars.BackBufferWidth = d_renderPars.resolutionWidth();
		d_presentPars.BackBufferHeight = d_renderPars.resolutionHeight();
		d_presentPars.BackBufferFormat = D3DFMT_A8R8G8B8;
		d_presentPars.BackBufferCount = 1;
		d_presentPars.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//d_presentPars.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d_presentPars.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		d_presentPars.hDeviceWindow = d_hWindow;
		d_presentPars.Windowed = d_renderPars.windowed();
		if (!d_renderPars.windowed())
			d_presentPars.FullScreen_RefreshRateInHz = d_renderPars.fullScreenRefreshRate();

		res = d_direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d_hWindow,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
			&d_presentPars, &d_renderDevice);
		if ((res != D3D_OK) || (d_renderDevice == nullptr))
		{
			echo("ERROR: Can't create RenderDevice.");
			return false;
		}

		d_renderDevice->SetRenderState(D3DRS_LIGHTING, false);
		d_renderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		d_renderDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		d_renderDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		d_renderDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		d_renderDevice->GetRenderTarget(0, &d_defaultRenderTarget);
		d_defaultRenderTarget->GetDesc(&d_defaultRenderTargetDesc);

		return true;
	}

  bool RenderMan::disposeRenderDevice()
	{
		if (d_renderDevice != nullptr)
		{
			d_renderDevice->Release();
			d_renderDevice = nullptr;
		}

		if (d_direct3d != nullptr)
		{
			d_direct3d->Release();
			d_direct3d = nullptr;
		}

		return true;
	}


} // ns Doh3d
