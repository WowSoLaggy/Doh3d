#include "PrecompiledHeader.h"
#include "ResourceMan.h"

#include "dirent.h"
#include "Utils.h"


namespace Doh3d
{

  std::string ResourceMan::d_textureDir = "";
  std::string ResourceMan::d_fontDir = "";

  std::vector<Texture> ResourceMan::d_textures;
  std::vector<RBitmapFont> ResourceMan::d_fonts;


  bool ResourceMan::init()
  {
    return true;
  }

  bool ResourceMan::dispose()
  {
    // Ignore return values, clear all anyway

    unloadResources();
    clearResources();

    return true;
  }


  bool ResourceMan::indexResources()
  {
    LOG("ResourceMan::indexResources()");

    // Index textures

    if (d_textureDir.empty())
    {
      echo("ERROR: Invalid texture dir.");
      return false;
    }

    DIR *dir = opendir(d_textureDir.c_str());
    if (dir == nullptr)
    {
      echo("ERROR: Can't find texture folder.");
      return false;
    }

    std::string textureDir = d_textureDir;
    if (!parseTextureDir(textureDir.append("\\")))
    {
      echo("ERROR: Can't parse texture directory.");
      return false;
    }

    // Index fonts

    if (d_fontDir.empty())
    {
      echo("ERROR: Invalid font dir.");
      return false;
    }

    dir = opendir(d_fontDir.c_str());
    if (dir == nullptr)
    {
      echo("ERROR: Can't find font folder.");
      return false;
    }

    std::string fontsDir = d_fontDir;
    if (!parseFontDir(fontsDir.append("\\")))
    {
      echo("ERROR: Can't parse font directory.");
      return false;
    }

    return true;
  }

  bool ResourceMan::reloadResources()
  {
    return loadResources(true);
  }

  bool ResourceMan::loadResources()
  {
    return loadResources(false);
  }

  bool ResourceMan::unloadResources()
  {
    LOG("ResourceManager::unloadResources()");

    for (auto& font : d_fonts)
    {
      if (!font.unload())
      {
        echo("ERROR: Can't unload font: \"", font.getFontName(), "\".");
        return false;
      }
    }

    for (auto& texture : d_textures)
    {
      if (!texture.unload())
      {
        echo("ERROR: Can't unload texture: \"", texture.getFilePath(), "\".");
        return false;
      }
    }

    return true;
  }

  bool ResourceMan::clearResources()
  {
    d_textures.clear();
    d_fonts.clear();

    return true;
  }


  bool ResourceMan::loadResources(bool pForceReload)
  {
    LOG("ResourceManager::loadResources()");

    if (d_textureDir.empty())
    {
      echo("ERROR: Invalid texture dir.");
      return false;
    }

    if (d_fontDir.empty())
    {
      echo("ERROR: Invalid font dir.");
      return false;
    }

    DIR* dir = opendir(d_textureDir.c_str());
    if (dir == nullptr)
    {
      echo("ERROR: Invalid texture dir.");
      return false;
    }
    closedir(dir);

    dir = opendir(d_fontDir.c_str());
    if (dir == nullptr)
    {
      echo("ERROR: Invalid font dir.");
      return false;
    }
    closedir(dir);

    for (auto& texture : d_textures)
    {
      bool res = pForceReload ? texture.reload() : texture.load();
      if (!res)
      {
        echo("ERROR: Can't load texture: \"", texture.getFilePath(), "\".");
        return false;
      }
    }

    for (auto& font : d_fonts)
    {
      if (!font.load())
      {
        echo("ERROR: Can't load font: \"", font.getFontName(), "\".");
        return false;
      }
    }

    return true;
  }


  Texture& ResourceMan::getTexture(TextureId pTi)
  {
    return d_textures[pTi];
  }

  Texture* ResourceMan::getTexture(const std::string& pTextureName)
  {
    LOG("ResourceMan::getTexture()");

    auto& it = std::find_if(d_textures.begin(), d_textures.end(), [&](auto& texture) { return pTextureName.compare(texture.getFilePath()) == 0; });
    if (it == d_textures.end())
    {
      echo("ERROR: Can't get texture: \"", pTextureName, "\".");
      return nullptr;
    }

    return &*it;
  }

  bool ResourceMan::getTi(const std::string& pTextureName, TextureId& pTi)
  {
    LOG("ResourceMan::getTi()");

    auto& it = std::find_if(d_textures.begin(), d_textures.end(), [&](auto& texture) { return pTextureName.compare(texture.getFilePath()) == 0; });
    if (it == d_textures.end())
    {
      echo("ERROR: Can't get TI for texture: \"", pTextureName, "\".");
      return false;
    }

    pTi = std::distance(d_textures.begin(), it);

    return true;
  }


  bool ResourceMan::createFontTexture(const std::string& pText, const std::string& pFont, LPDIRECT3DTEXTURE9& pTexture,
                                      int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets)
  {
    LOG("ResourceMan::createFontTexture()");

    std::string fontPath = "";
    fontPath.append(pFont).append(".fnt");

    auto& it = std::find_if(d_fonts.begin(), d_fonts.end(), [&](auto& font) { return fontPath.compare(font.getFontName()) == 0; });
    if (it == d_fonts.end())
    {
      echo("ERROR: Can't find font: \"", pFont, "\".");
      return false;
    }

    if (it->getFontTexture(pText, pTexture, pTexWidth, pTexHeight, pCharOffsets))
    {
      echo("ERROR: Can't get font texture for font: \"", pFont, "\".");
      return false;
    }

    return true;
  }


  bool ResourceMan::parseTextureDir(const std::string& pDir)
  {
    LOG("ResourceMan::parseTextureDir()");

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
        auto tokens = splitString(textureFileName, '_');
        if (tokens.size() != 5) // name, width, height, #frames, alphaCheck
        {
          echo("ERROR: Invalid texture file name: \"", textureFileName, "\".");
          return false;
        }
        int finalToken = tokens.size() - 1;

        d_textures.push_back(Texture(
          textureFileName,
          D3DXVECTOR2((FLOAT)std::stoi(tokens[1]), (FLOAT)std::stoi(tokens[2])), std::stoi(tokens[3]),
          splitString(tokens[4], '.')[0] == "a"));
      }
      else if ((ent->d_type == DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        parseFontDir(strTemp.append(ent->d_name, ent->d_namlen).append("\\"));
    }

    return true;
  }

  bool ResourceMan::parseFontDir(const std::string& pDir)
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
        d_fonts.push_back(strTemp.append(ent->d_name, ent->d_namlen).erase(0, pDir.size()));
      else if ((ent->d_type == DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        parseFontDir(strTemp.append(ent->d_name, ent->d_namlen).append("\\"));
    }

    return true;
  }

} // ns Doh3d
