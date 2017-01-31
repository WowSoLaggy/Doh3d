#pragma once

#ifndef INC_DOH3D_RESOURCEMAN_H
#define INC_DOH3D_RESOURCEMAN_H


#include "Texture.h"
#include "RBitmapFont.h"


namespace Doh3d
{

  using TextureId = int;


  class ResourceMan
  {
  public:

    static bool init();
    static bool dispose();

    static bool reloadResources();
    static bool loadResources();
    static bool unloadResources();


    static void setTextureDir(const std::string& pTextureDir) { d_textureDir = pTextureDir; }
    static void setFontDir(const std::string& pFontDir) { d_fontDir = pFontDir; }

    static const std::string& getTextureDir() { return d_textureDir; }
    static const std::string& getFontDir() { return d_fontDir; }


    static Texture& getTexture(TextureId pTi);
    static Texture* getTexture(const std::string& pTextureName);
    static bool getTi(const std::string& pTextureName, TextureId& pTi);

    // TODO: Move to some separate class
    static bool createFontTexture(const std::string& pText, const std::string& pFont, LPDIRECT3DTEXTURE9& pTexture,
                                  int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets);

  private:

    static std::string d_textureDir;
    static std::string d_fontDir;

    static std::vector<Texture> d_textures;
    static std::vector<RBitmapFont> d_fonts;


    static bool loadResources(bool pForceReload);

    static bool parseTextureDir(const std::string& pDir);
    static bool parseFontDir(const std::string& pDir);

  };

} // ns Doh3d


#endif // INC_DOH3D_RESOURCEMAN_H
