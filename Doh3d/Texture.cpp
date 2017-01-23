#include "Doh3d.h"
#include "Texture.h"


namespace Doh3d
{

  bool Texture::Load()
	{
		LOG("RTexture::Load()");
		HRESULT hRes;

		std::string strTemp = ResourceMan::GetTextureDir();

		hRes = D3DXCreateTextureFromFileEx(RenderMan::GetRenderDevice(), strTemp.append("\\").append(m_filePath).c_str(),
										   D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_texture);
		if (hRes != S_OK || !m_texture)
		{
			echo("ERROR: Can't create texture from file: \"", m_filePath, "\".");
			return false;
		}

		if ((m_size.x == 0) && (m_size.y == 0))
		{
			D3DSURFACE_DESC surfaceDesc;
			m_texture->GetLevelDesc(0, &surfaceDesc);
			m_size = D3DXVECTOR2((float)surfaceDesc.Width, (float)surfaceDesc.Height);
			m_size2 = m_size / 2;
		}

		m_alphaMap.Init(m_alphaCheck, m_texture);

		return true;
	}

  bool Texture::Unload()
	{
		if (m_texture != nullptr)
		{
			m_texture->Release();
			m_texture = nullptr;
		}

		return true;
	}


	bool Texture::HitTest(int pX, int pY, int pFrame) const
	{
		if (pX < 0 || pY < 0 || pX >= m_size.x || pY >= m_size.y)
			return false;

		return m_alphaMap.Check(pX + pFrame * (int)m_size.x, pY);
	}

	bool Texture::HitTest(float pX, float pY, int pFrame) const
	{
		return HitTest((int)pX, (int)pY, pFrame);
	}

	bool Texture::HitTest(const D3DXVECTOR2& pCoords, int pFrame) const
	{
		return HitTest((int)pCoords.x, (int)pCoords.y, pFrame);
	}

	bool Texture::HitTest(const D3DXVECTOR3& pCoords, int pFrame) const
	{
		return HitTest((int)pCoords.x, (int)pCoords.y, pFrame);
	}

	RECT Texture::GetFrame(int pFrameNumber)
	{
		RECT rect;
		rect.left = (LONG)(m_size.x * pFrameNumber);
		rect.top = 0;
		rect.right = (LONG)(m_size.x * (pFrameNumber + 1));
		rect.bottom = (LONG)(m_size.y);
		return rect;
	}

} // ns Doh3d
