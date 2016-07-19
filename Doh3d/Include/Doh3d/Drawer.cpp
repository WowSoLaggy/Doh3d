#include "..\Doh3d.h"
#include "Drawer.h"


namespace Doh3d
{

	ErrCode Drawer::BeginScene()
	{
		LOG("Drawer::BeginScene()");
		int hRes = 0;

		hRes = RenderMan::GetRenderDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		if (hRes != 0)
		{
			echo("ERROR: Can't clear RenderDevice.");
			return err_cantBeginScene;
		}

		hRes = RenderMan::GetRenderDevice()->BeginScene();
		if (hRes != 0)
		{
			echo("ERROR: Can't begin RenderDevice scene.");
			return err_cantBeginScene;
		}

		return err_noErr;
	}

	ErrCode Drawer::EndScene()
	{
		LOG("Drawer::EndScene()");
		int hRes = 0;

		hRes = RenderMan::GetRenderDevice()->EndScene();
		if (hRes != 0)
		{
			echo("ERROR: Can't end RenderDevice scene.");
			return err_cantEndScene;
		}

		hRes = RenderMan::GetRenderDevice()->Present(NULL, NULL, NULL, NULL);
		if (hRes != 0)
		{
			echo("ERROR: Can't present RenderDevice.");
			return err_cantEndScene;
		}

		return err_noErr;
	}

} // ns Doh3d
