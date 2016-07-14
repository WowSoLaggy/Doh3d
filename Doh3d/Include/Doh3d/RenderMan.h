#pragma once

#ifndef RENDERMAN_H
#define RENDERMAN_H


#include "RenderPars.h"
#include "StartupPars.h"


namespace Doh3d
{

	class RenderMan
	{
	public:

		static bool IsCreated() { return m_isCreated; }
		static IDirect3DDevice9 *& GetRenderDevice() { return m_renderDevice; }
		static HWND & GetHWindow() { return m_hWindow; }

		static ErrCode Recreate(RenderPars &pRenderPars, StartupPars &pStartupPars);
		static ErrCode Dispose();

	private:

		static bool m_isCreated;

		static HWND m_hWindow;
		static IDirect3D9 *m_direct3d;
		static D3DPRESENT_PARAMETERS m_presentPars;
		static D3DCAPS9 m_caps;
		static IDirect3DDevice9 *m_renderDevice;
		static LPDIRECT3DSURFACE9 m_defaultRenderTarget;
		static D3DSURFACE_DESC m_defaultRenderTargetDesc;

		static ErrCode CreateWnd(RenderPars &pRenderPars, StartupPars &pStartupPars);
		static ErrCode DisposeWnd();

		static ErrCode CreateRenderDevice(RenderPars &pRenderPars);
		static ErrCode DisposeRenderDevice();

	};

} // ns Doh3d


#endif // RENDERMAN_H
