#include "PrecompiledHeader.h"
#include "Drawer.h"


namespace Doh3d
{

  bool Drawer::beginScene()
	{
		LOG("Drawer::beginScene()");
		int hRes = 0;

    // TODO: Think of something for color (maybe pass it as a parameter?)
    //D3DCOLOR clearColor = D3DCOLOR_ARGB(255, 101, 156, 239);
    D3DCOLOR clearColor = D3DCOLOR_ARGB(255, 0, 0, 0);

		hRes = RenderMan::getRenderDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor, 1.0f, 0);
		if (hRes != 0)
		{
			echo("ERROR: Can't clear RenderDevice.");
			return false;
		}

		hRes = RenderMan::getRenderDevice()->BeginScene();
		if (hRes != 0)
		{
			echo("ERROR: Can't begin RenderDevice scene.");
			return false;
		}

		return true;
	}

  bool Drawer::endScene()
	{
		LOG("Drawer::endScene()");
		int hRes = 0;

		hRes = RenderMan::getRenderDevice()->EndScene();
		if (hRes != 0)
		{
			echo("ERROR: Can't end RenderDevice scene.");
			return false;
		}

		hRes = RenderMan::getRenderDevice()->Present(NULL, NULL, NULL, NULL);
		if (hRes != 0)
		{
			echo("ERROR: Can't present RenderDevice.");
			return false;
		}

		return true;
	}

} // ns Doh3d
