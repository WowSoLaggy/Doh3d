#include "Doh3d.h"
#include "ResourceMan.h"

#include "dirent.h"


namespace Doh3d
{

	std::string ResourceMan::m_textureDir = "";
	std::string ResourceMan::m_fontDir = "";

	std::vector<Texture> ResourceMan::m_textures;
	std::vector<RBitmapFont> ResourceMan::m_fonts;


	ErrCode3d ResourceMan::LoadResources()
	{
		LOG("ResourceManager::LoadResources()");
		ErrCode3d err3d;

		if (m_textureDir.empty())
		{
			echo("ERROR: Invalid texture dir.");
			return err3d_invalidTextureDir;
		}

		if (m_fontDir.empty())
		{
			echo("ERROR: Invalid font dir.");
			return err3d_invalidFontDir;
		}

		DIR* dir = opendir(m_textureDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Invalid texture dir.");
			return err3d_invalidTextureDir;
		}
		closedir(dir);

		dir = opendir(m_fontDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Invalid font dir.");
			return err3d_invalidTextureDir;
		}
		closedir(dir);

		for (auto& texture : m_textures)
		{
			err3d = texture.Load();
			if (err3d != err3d_noErr)
			{
				echo("ERROR: Can't load texture: \"", texture.GetFilePath(), "\".");
				return err3d;
			}
		}

		for (auto& font : m_fonts)
		{
			err3d = font.Load();
			if (err3d != err3d_noErr)
			{
				echo("ERROR: Can't load font: \"", font.GetFontName(), "\".");
				return err3d;
			}
		}

		return err3d_noErr;
	}

	ErrCode3d ResourceMan::UnloadResources()
	{
		LOG("ResourceManager::UnloadResources()");
		ErrCode3d err3d;

		for (auto& font : m_fonts)
		{
			err3d = font.Unload();
			if (err3d != err3d_noErr)
			{
				echo("ERROR: Can't unload font: \"", font.GetFontName(), "\".");
				return err3d;
			}
		}

		for (auto& texture : m_textures)
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


	ErrCode3d ResourceMan::AddTexture(const std::string& pFilePath, D3DXVECTOR2 pSize, int pTotalFrames)
	{
		m_textures.emplace_back(pFilePath, pSize, pTotalFrames);
		return err3d_noErr;
	}

	ErrCode3d ResourceMan::AddFont(const std::string& pFontPath)
	{
		m_fonts.emplace_back(pFontPath);
		return err3d_noErr;
	}


	Texture ResourceMan::GetTexture(int pTi)
	{
		return m_textures[pTi];
	}

	ErrCode3d ResourceMan::GetTi(const std::string& pTextureName, int& pTi)
	{
		LOG("ResourceManager::GetTi()");

		auto& it = std::find_if(m_textures.begin(), m_textures.end(), [&](auto& texture) { return pTextureName.compare(texture.GetFilePath()) == 0; });
		if (it == m_textures.end())
		{
			echo("ERROR: Can't get ti for texture: \"", pTextureName, "\".");
			return err3d_textureNotFound;
		}

		pTi = std::distance(m_textures.begin(), it);

		return err3d_noErr;
	}

	ErrCode3d ResourceMan::CreateFontTexture(const std::string& pText, const std::string& pFont, LPDIRECT3DTEXTURE9& pTexture,
											 int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets)
	{
		LOG("ResourceMan::GetFontTexture()");
		ErrCode3d err;

		std::string fontPath = "\\";
		fontPath.append(pFont).append(".fnt");

		auto& it = std::find_if(m_fonts.begin(), m_fonts.end(), [&](auto& font) { return fontPath.compare(font.GetFontName()) == 0; });
		if (it == m_fonts.end())
		{
			echo("ERROR: Can't find font: \"", pFont, "\".");
			return err3d_fontNotFound;
		}

		err = it->GetFontTexture(pText, pTexture, pTexWidth, pTexHeight, pCharOffsets);
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't get font texture for font: \"", pFont, "\".");
			return err;
		}

		return err3d_noErr;
	}
	
} // ns Doh3d
