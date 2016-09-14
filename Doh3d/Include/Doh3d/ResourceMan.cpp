#include "../Doh3d.h"
#include "ResourceMan.h"

#include "dirent.h"


namespace Doh3d
{

	std::string ResourceMan::m_texturesDir = "";
	std::vector<Texture> ResourceMan::m_textures;


	Texture ResourceMan::GetTexture(int pTi)
	{
		return m_textures[pTi];
	}


	ErrCode3d ResourceMan::SetTexturesDir(const std::string &pTexturesDir)
	{
		m_texturesDir = pTexturesDir;
		return err3d_noErr;
	}

	ErrCode3d ResourceMan::AddTexture(const std::string & pFilePath, D3DXVECTOR2 pSize, int pTotalFrames)
	{
		m_textures.emplace_back(pFilePath, pSize, pTotalFrames);
		return err3d_noErr;
	}

	ErrCode3d ResourceMan::GetTi(const std::string &pTextureName, int &pTi)
	{
		LOG("ResourceManager::GetTi()");

		auto & it = std::find_if(m_textures.begin(), m_textures.end(), [&](auto texture) { return pTextureName.compare(texture.GetFilePath()) == 0; });
		if (it == m_textures.end())
		{
			echo("ERROR: Can't get ti for texture: \"", pTextureName, "\".");
			return err3d_textureNotFound;
		}

		pTi = std::distance(m_textures.begin(), it);

		return err3d_noErr;
	}


	ErrCode3d ResourceMan::LoadResources()
	{
		LOG("ResourceManager::LoadResources()");
		ErrCode3d err3d;
		
		if (m_texturesDir.empty())
		{
			echo("ERROR: Invalid textures' dir.");
			return err3d_invalidTextureDir;
		}

		DIR *dir = opendir(m_texturesDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Invalid textures' dir.");
			return err3d_invalidTextureDir;
		}
		closedir(dir);

		for (auto & texture : m_textures)
		{
			err3d = texture.Load();
			if (err3d != err3d_noErr)
			{
				echo("ERROR: Can't load texture: \"", texture.GetFilePath(), "\".");
				return err3d;
			}
		}

		return err3d_noErr;
	}

	ErrCode3d ResourceMan::UnloadResources()
	{
		LOG("ResourceManager::UnloadResources()");
		ErrCode3d err3d;

		for (auto & texture : m_textures)
		{
			err3d = texture.Unload();
			if (err3d != err3d_noErr)
			{
				echo("ERROR: Can't unload texture: \"", texture.GetFilePath(), "\".");
				return err3d;
			}
		}

		return err3d_noErr;
	}

} // ns Doh3d
