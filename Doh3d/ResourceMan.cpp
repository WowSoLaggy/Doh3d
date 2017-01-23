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


  bool ResourceMan::Init()
	{
		LOG("ResourceMan::Init()");

		// Index textures

		if (m_textureDir.empty())
		{
			echo("ERROR: Invalid texture dir.");
			return false;
		}
		
		DIR *dir = opendir(m_textureDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Can't find texture folder.");
			return false;
		}

		std::string textureDir = m_textureDir;
		if (ParseTextureDir(textureDir.append("\\")))
		{
			echo("ERROR: Can't parse texture directory.");
			return false;
		}

		// Index fonts

		if (m_fontDir.empty())
		{
			echo("ERROR: Invalid font dir.");
			return false;
		}

		dir = opendir(m_fontDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Can't find font folder.");
			return false;
		}

		std::string fontsDir = m_fontDir;
		if (ParseFontDir(fontsDir.append("\\")))
		{
			echo("ERROR: Can't parse font directory.");
			return false;
		}

		return true;
	}

  bool ResourceMan::Dispose()
	{
		return true;
	}


  bool ResourceMan::LoadResources()
	{
		LOG("ResourceManager::LoadResources()");

		if (m_textureDir.empty())
		{
			echo("ERROR: Invalid texture dir.");
			return false;
		}

		if (m_fontDir.empty())
		{
			echo("ERROR: Invalid font dir.");
			return false;
		}

		DIR* dir = opendir(m_textureDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Invalid texture dir.");
			return false;
		}
		closedir(dir);

		dir = opendir(m_fontDir.c_str());
		if (dir == nullptr)
		{
			echo("ERROR: Invalid font dir.");
			return false;
		}
		closedir(dir);

		for (auto& texture : m_textures)
		{
			if (!texture.Load())
			{
				echo("ERROR: Can't load texture: \"", texture.GetFilePath(), "\".");
				return false;
			}
		}

		for (auto& font : m_fonts)
		{
			if (!font.Load())
			{
				echo("ERROR: Can't load font: \"", font.GetFontName(), "\".");
				return false;
			}
		}

		return true;
	}

  bool ResourceMan::UnloadResources()
	{
		LOG("ResourceManager::UnloadResources()");

		for (auto& font : m_fonts)
		{
			if (!font.Unload())
			{
				echo("ERROR: Can't unload font: \"", font.GetFontName(), "\".");
				return false;
			}
		}

		for (auto& texture : m_textures)
		{
			if (!texture.Unload())
			{
				echo("ERROR: Can't unload texture: \"", texture.GetFilePath(), "\".");
				return false;
			}
		}

		return true;
	}


	Texture ResourceMan::GetTexture(int pTi)
	{
		return m_textures[pTi];
	}

  bool ResourceMan::GetTi(const std::string& pTextureName, int& pTi)
	{
		LOG("ResourceManager::GetTi()");

		auto& it = std::find_if(m_textures.begin(), m_textures.end(), [&](auto& texture) { return pTextureName.compare(texture.GetFilePath()) == 0; });
		if (it == m_textures.end())
		{
			echo("ERROR: Can't get ti for texture: \"", pTextureName, "\".");
			return false;
		}

		pTi = std::distance(m_textures.begin(), it);

		return true;
	}

  bool ResourceMan::CreateFontTexture(const std::string& pText, const std::string& pFont, LPDIRECT3DTEXTURE9& pTexture,
											 int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets)
	{
		LOG("ResourceMan::CreateFontTexture()");

		std::string fontPath = "";
		fontPath.append(pFont).append(".fnt");

		auto& it = std::find_if(m_fonts.begin(), m_fonts.end(), [&](auto& font) { return fontPath.compare(font.GetFontName()) == 0; });
		if (it == m_fonts.end())
		{
			echo("ERROR: Can't find font: \"", pFont, "\".");
			return false;
		}

		if (it->GetFontTexture(pText, pTexture, pTexWidth, pTexHeight, pCharOffsets))
		{
			echo("ERROR: Can't get font texture for font: \"", pFont, "\".");
			return false;
		}

		return true;
	}


  bool ResourceMan::ParseTextureDir(const std::string& pDir)
	{
		LOG("ResourceMan::ParseFontDir()");

		struct dirent *ent;

		DIR *dir = opendir(pDir.c_str());
		if (dir == nullptr)
			return false;

		while (true)
		{
			ent = readdir(dir);

			if (ent == nullptr)
				return true;

			std::string strTemp = pDir;

			std::regex pattern("\\w*.(jpg|png|bmp)");

			if ((ent->d_type == DT_REG) && (std::regex_match(ent->d_name, pattern)))
			{
				// Parse texture file name

				std::string textureFileName = strTemp.append(ent->d_name, ent->d_namlen).erase(0, pDir.size());
				auto tokens = SplitString(textureFileName, '_');
				if (tokens.size() != 5) // name, width, height, #frames, alphaCheck
				{
					echo("ERROR: Invalid texture file name: \"", textureFileName, "\".");
					return false;
				}
				int finalToken = tokens.size() - 1;

				m_textures.push_back(Texture(
					textureFileName,
					D3DXVECTOR2((FLOAT)std::stoi(tokens[1]), (FLOAT)std::stoi(tokens[2])), std::stoi(tokens[3]),
					SplitString(tokens[4], '.')[0] == "a"));
			}
			else if ((ent->d_type == DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				ParseFontDir(strTemp.append(ent->d_name, ent->d_namlen).append("\\"));
		}

		return true;
	}

  bool ResourceMan::ParseFontDir(const std::string& pDir)
	{
		struct dirent *ent;

		DIR *dir = opendir(pDir.c_str());
		if (dir == nullptr)
			return false;

		while (true)
		{
			ent = readdir(dir);

			if (ent == nullptr)
				return true;

			std::string strTemp = pDir;

			std::regex pattern("\\w*.fnt");

			if ((ent->d_type == DT_REG) && (std::regex_match(ent->d_name, pattern)))
				m_fonts.push_back(strTemp.append(ent->d_name, ent->d_namlen).erase(0, pDir.size()));
			else if ((ent->d_type == DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				ParseFontDir(strTemp.append(ent->d_name, ent->d_namlen).append("\\"));
		}

		return true;
	}
	
} // ns Doh3d
