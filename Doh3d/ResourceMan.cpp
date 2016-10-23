#include "Doh3d.h"
#include "ResourceMan.h"

#include "dirent.h"
#include "Utils.h"


namespace Doh3d
{

	std::string ResourceMan::m_textureDir = "";
	std::string ResourceMan::m_fontDir = "";

	std::vector<Texture> ResourceMan::m_textures;
	std::vector<RBitmapFont> ResourceMan::m_fonts;


	ErrCode3d ResourceMan::Init()
	{
		LOG("ResourceMan::Init()");
		ErrCode3d err3d;

		// Index textures

		if (m_textureDir.empty())
		{
			echo("ERROR: Invalid texture dir.");
			return err3d_invalidTextureDir;
		}
		
		DIR *dir = opendir(m_textureDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Can't find texture folder.");
			return err3d_invalidTextureDir;
		}

		std::string textureDir = m_textureDir;
		err3d = ParseTextureDir(textureDir.append("\\"));
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't parse texture directory.");
			return err3d;
		}

		// Index fonts

		if (m_fontDir.empty())
		{
			echo("ERROR: Invalid font dir.");
			return err3d_invalidFontDir;
		}

		dir = opendir(m_fontDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Can't find font folder.");
			return err3d_invalidFontDir;
		}

		std::string fontsDir = m_fontDir;
		err3d = ParseFontDir(fontsDir.append("\\"));
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't parse font directory.");
			return err3d;
		}

		return err3d_noErr;
	}

	ErrCode3d ResourceMan::Dispose()
	{
		return err3d_noErr;
	}


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
		LOG("ResourceMan::CreateFontTexture()");
		ErrCode3d err;

		std::string fontPath = "";
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


	ErrCode3d ResourceMan::ParseTextureDir(const std::string& pDir)
	{
		LOG("ResourceMan::ParseFontDir()");

		struct dirent *ent;

		DIR *dir = opendir(pDir.c_str());
		if (dir == nullptr)
			return err3d_noFontsFolder;

		while (true)
		{
			ent = readdir(dir);

			if (ent == nullptr)
				return err3d_noErr;

			std::string strTemp = pDir;

			std::regex pattern("\\w*.(jpg|png|bmp)");

			if ((ent->d_type == DT_REG) && (std::regex_match(ent->d_name, pattern)))
			{
				// Parse texture file name

				std::string textureFileName = strTemp.append(ent->d_name, ent->d_namlen).erase(0, pDir.size());
				auto tokens = SplitString(textureFileName, '_');
				if (tokens.size() < 4) // 4 are: name, width, height, #frames
				{
					echo("ERROR: Invalid texture file name: \"", textureFileName, "\".");
					return err3d_cantParseTextureFileName;
				}
				int finalToken = tokens.size() - 1;

				m_textures.push_back(Texture(
					textureFileName,
					D3DXVECTOR2((FLOAT)std::stoi(tokens[finalToken - 2]), (FLOAT)std::stoi(tokens[finalToken - 1])),
					std::stoi(SplitString(tokens[finalToken], '.')[0])));
			}
			else if ((ent->d_type == DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				ParseFontDir(strTemp.append(ent->d_name, ent->d_namlen).append("\\"));
		}

		return err3d_noErr;
	}

	ErrCode3d ResourceMan::ParseFontDir(const std::string& pDir)
	{
		struct dirent *ent;

		DIR *dir = opendir(pDir.c_str());
		if (dir == nullptr)
			return err3d_noTexturesFolder;

		while (true)
		{
			ent = readdir(dir);

			if (ent == nullptr)
				return err3d_noErr;

			std::string strTemp = pDir;

			std::regex pattern("\\w*.fnt");

			if ((ent->d_type == DT_REG) && (std::regex_match(ent->d_name, pattern)))
				m_fonts.push_back(strTemp.append(ent->d_name, ent->d_namlen).erase(0, pDir.size()));
			else if ((ent->d_type == DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				ParseFontDir(strTemp.append(ent->d_name, ent->d_namlen).append("\\"));
		}

		return err3d_noErr;
	}
	
} // ns Doh3d
