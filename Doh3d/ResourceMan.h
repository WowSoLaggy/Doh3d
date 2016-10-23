#pragma once

#ifndef INC_DOH3D_RESOURCEMAN_H
#define INC_DOH3D_RESOURCEMAN_H


#include "Texture.h"
#include "RBitmapFont.h"


namespace Doh3d
{

	class ResourceMan
	{
	public:

		static ErrCode3d Init();
		static ErrCode3d Dispose();

		static ErrCode3d LoadResources();
		static ErrCode3d UnloadResources();


		static void SetTextureDir(const std::string& pTextureDir) { m_textureDir = pTextureDir; }
		static void SetFontDir(const std::string& pFontDir) { m_fontDir = pFontDir; }
		static const std::string& GetTextureDir() { return m_textureDir; }
		static const std::string& GetFontDir() { return m_fontDir; }


		static Texture GetTexture(int pTi);
		static ErrCode3d GetTi(const std::string& pTextureName, int& pTi);
		static ErrCode3d CreateFontTexture(const std::string& pText, const std::string& pFont, LPDIRECT3DTEXTURE9& pTexture,
										   int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets);

	private:

		static std::string m_textureDir;
		static std::string m_fontDir;

		static std::vector<Texture> m_textures;
		static std::vector<RBitmapFont> m_fonts;


		static ErrCode3d ParseTextureDir(const std::string& pDir);
		static ErrCode3d ParseFontDir(const std::string& pDir);

	};

} // ns Doh3d


#endif // INC_DOH3D_RESOURCEMAN_H
