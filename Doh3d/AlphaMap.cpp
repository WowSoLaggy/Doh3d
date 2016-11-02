#include "Doh3d.h"
#include "AlphaMap.h"


namespace Doh3d
{

	ErrCode3d AlphaMap::Init(LPDIRECT3DTEXTURE9 pTexture)
	{
		D3DSURFACE_DESC surfaceDesc;
		pTexture->GetLevelDesc(0, &surfaceDesc);

		m_width = surfaceDesc.Width;
		m_height = surfaceDesc.Height;
		m_mask.resize(m_width * m_height);

		m_solid = true;
		
		D3DLOCKED_RECT lockedRect;
		if (SUCCEEDED(pTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD)))
		{
			unsigned char* bits = (unsigned char*)lockedRect.pBits;

			for (int y = 0; y < m_height; ++y)
			{
				for (int x = 0; x < m_width; ++x)
				{
					bool solid = (bits[x * 4 + y * lockedRect.Pitch + 3] != 0);
					m_mask[x + y * m_width] = solid;
					if (!solid)
						m_solid = false;
				}
			}
			pTexture->UnlockRect(0);
		}

		return err3d_noErr;
	}


	bool AlphaMap::Check(int pX, int pY) const
	{
		if (m_solid)
			return true;

		return m_mask[pX + pY * m_width];
	}

} // ns Doh3d
