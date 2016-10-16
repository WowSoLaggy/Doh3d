#pragma once

#ifndef INC_DOH3D_RENDERMAN_H
#define INC_DOH3D_RENDERMAN_H


#include "RenderPars.h"
#include "StartupPars.h"


namespace Doh3d
{

	class RenderMan
	{
	public:

		static bool IsCreated() { return m_isCreated; }
		static const RenderPars& GetRenderPars() { return m_renderPars; }
		static const LPDIRECT3DDEVICE9& GetRenderDevice() { return m_renderDevice; }
		static const HWND& GetHWindow() { return m_hWindow; }

		static ErrCode3d Recreate(const RenderPars& pRenderPars);
		static ErrCode3d Dispose();

	private:

		static bool m_isCreated;
		static RenderPars m_renderPars;

		static HWND m_hWindow;
		static LPDIRECT3D9 m_direct3d;
		static D3DPRESENT_PARAMETERS m_presentPars;
		static D3DCAPS9 m_caps;
		static LPDIRECT3DDEVICE9 m_renderDevice;
		static LPDIRECT3DSURFACE9 m_defaultRenderTarget;
		static D3DSURFACE_DESC m_defaultRenderTargetDesc;

		static ErrCode3d CreateWnd(const StartupPars& pStartupPars);
		static ErrCode3d DisposeWnd();

		static ErrCode3d CreateRenderDevice();
		static ErrCode3d DisposeRenderDevice();

	};

} // ns Doh3d


#endif // INC_DOH3D_RENDERMAN_H
