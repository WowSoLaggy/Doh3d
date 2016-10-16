#include "Doh3d.h"
#include "Texture.h"


namespace Doh3d
{

	ErrCode3d Texture::Load()
	{
		LOG("RTexture::Load()");
		HRESULT hRes;

		std::string strTemp = ResourceMan::GetTextureDir();

		hRes = D3DXCreateTextureFromFileEx(RenderMan::GetRenderDevice(), strTemp.append("\\").append(m_filePath).c_str(),
										   D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_texture);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create texture from file: \"", m_filePath, "\".");
			return err3d_cantLoadTexture;
		}

		if ((m_size.x == 0) && (m_size.y == 0))
		{
			D3DSURFACE_DESC surfaceDesc;
			m_texture->GetLevelDesc(0, &surfaceDesc);
			m_size = D3DXVECTOR2((float)surfaceDesc.Width, (float)surfaceDesc.Height);
		}

		return err3d_noErr;
	}

	ErrCode3d Texture::Unload()
	{
		if (m_texture != nullptr)
		{
			m_texture->Release();
			m_texture = nullptr;
		}

		return err3d_noErr;
	}

} // ns Doh3d
