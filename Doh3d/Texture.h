#pragma once

#ifndef INC_DOH3D_TEXTURE_H
#define INC_DOH3D_TEXTURE_H


namespace Doh3d
{

	class Texture
	{
	public:

		Texture(const std::string& pFilePath, D3DXVECTOR2 pSize, int pTotalFrames)
			: m_filePath(pFilePath), m_size(pSize), m_totalFrames(pTotalFrames), m_texture(nullptr) { }


		const std::string& GetFilePath() const { return m_filePath; }
		LPDIRECT3DTEXTURE9 Get() { return m_texture; }
		D3DXVECTOR2 GetSize() const { return m_size; }


		ErrCode3d Load();
		ErrCode3d Unload();

	private:

		std::string m_filePath;
		D3DXVECTOR2 m_size;
		int m_totalFrames;

		LPDIRECT3DTEXTURE9 m_texture;

	};

} // Doh3d


#endif // INC_DOH3D_TEXTURE_H
