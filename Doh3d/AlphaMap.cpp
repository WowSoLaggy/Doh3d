#include "Doh3d.h"
#include "AlphaMap.h"


namespace Doh3d
{

	bool AlphaMap::init(bool pAlphaCheck, LPDIRECT3DTEXTURE9 pTexture)
	{
    d_solid = true;

		if (!pAlphaCheck)
			return false;

		D3DSURFACE_DESC surfaceDesc;
		pTexture->GetLevelDesc(0, &surfaceDesc);

		d_width = surfaceDesc.Width;
		d_height = surfaceDesc.Height;
		d_mask.resize(d_width * d_height);

		D3DLOCKED_RECT lockedRect;
		if (SUCCEEDED(pTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD)))
		{
			unsigned char* bits = (unsigned char*)lockedRect.pBits;

			for (int y = 0; y < d_height; ++y)
			{
				for (int x = 0; x < d_width; ++x)
				{
					bool solid = (bits[x * 4 + y * lockedRect.Pitch + 3] != 0);
					d_mask[x + y * d_width] = solid;
					if (!solid)
						d_solid = false;
				}
			}
			pTexture->UnlockRect(0);
		}

		return true;
	}


	bool AlphaMap::check(int pX, int pY) const
	{
		// TODO: Alpha map check for the current frame, not for the whole texture

		if (d_solid)
			return true;

		return d_mask[pX + pY * d_width];
	}

} // ns Doh3d
