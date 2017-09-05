#pragma once

#include "RenderPars.h"
#include "WinClass.h"


namespace Doh3d
{

  class RenderMan
  {
  public:

    static bool isCreated() { return d_isCreated; }
    static const RenderPars& getRenderPars() { return d_renderPars; }
    static const LPDIRECT3DDEVICE9& getRenderDevice() { return d_renderDevice; }
    static const HWND& getHWindow() { return d_hWindow; }

    static bool init();
    static bool dispose();

    static bool recreate(const RenderPars& pRenderPars, const std::string& pWindowCaption);

  private:

    static bool d_isCreated;
    static RenderPars d_renderPars;

    static HWND d_hWindow;
    static LPDIRECT3D9 d_direct3d;
    static D3DPRESENT_PARAMETERS d_presentPars;
    static D3DCAPS9 d_caps;
    static LPDIRECT3DDEVICE9 d_renderDevice;
    static LPDIRECT3DSURFACE9 d_defaultRenderTarget;
    static D3DSURFACE_DESC d_defaultRenderTargetDesc;

    static bool createWnd(const std::string& pWindowCaption);
    static bool disposeWnd();

    static bool createRenderDevice();
    static bool disposeRenderDevice();

  };

} // ns Doh3d
