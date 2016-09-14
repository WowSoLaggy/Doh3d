#pragma once

#ifndef DOH3D_RESOURCEMAN_H
#define DOH3D_RESOURCEMAN_H


#include "Texture.h"


namespace Doh3d
{

	class ResourceMan
	{
	public:

		static Texture GetTexture(int pTi);


		static ErrCode3d SetTexturesDir(const std::string &pTexturesDir);
		static const std::string & GetTexturesDir() { return m_texturesDir; }

		static ErrCode3d AddTexture(const std::string & pFilePath, D3DXVECTOR2 pSize, int pTotalFrames);
		static ErrCode3d GetTi(const std::string &pTextureName, int &pTi);

		static ErrCode3d LoadResources();
		static ErrCode3d UnloadResources();

	private:

		static std::string m_texturesDir;

		static std::vector<Texture> m_textures;

	};

} // ns Doh3d


#endif // DOH3D_RESOURCEMAN_H
