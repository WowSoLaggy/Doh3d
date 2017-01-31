#include "PrecompiledHeader.h"
#include "RBitmapFont.h"

#include "RenderMan.h"
#include "ResourceMan.h"


namespace Doh3d
{

	RBitmapFont::RBitmapFont(const std::string& pFontName)
	{
		d_fontName = pFontName;
		d_charsetPath = "";
		d_charsetTexture = nullptr;
	}

	RBitmapFont::~RBitmapFont()
	{
	}

  bool RBitmapFont::load()
	{
		LOG("BFont::load()");
		int hRes;

		// Parse .fnt file

		std::string fntPath = "";
		fntPath.append(ResourceMan::getFontDir()).append(d_fontName);
		if (!parseFntFile(fntPath))
		{
			echo("ERROR: Can't parse .fnt file: \"", fntPath, "\".");
			return false;
		}

		d_charsetPath.insert(0, ResourceMan::getFontDir());

		// Read texture

		hRes = D3DXCreateTextureFromFileEx(RenderMan::getRenderDevice(), d_charsetPath.c_str(),
										   D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_SYSTEMMEM, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &d_charsetTexture);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create texture for font: \"", d_fontName, "\".");
			return false;
		}

		return true;
	}

  bool RBitmapFont::unload()
	{
		if (d_charsetTexture != nullptr)
		{
			d_charsetTexture->Release();
			d_charsetTexture = nullptr;
		}

		std::vector<BitmapChar>().swap(d_chars);

		return true;
	}

  bool RBitmapFont::getFontTexture(const std::string& pText, LPDIRECT3DTEXTURE9& pTexture, int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets)
	{
		LOG("BFont::getFontTexture()");
		int hRes;

		if (pText.empty())
		{
			pTexture = nullptr;
			return false;
		}

		// Get overall text width and height

		pTexWidth = 0;
		pTexHeight = d_lineHeight;

		for (unsigned int i = 0; i < pText.size(); ++i)
		{
			if (d_chars[pText[i]].Width > (d_chars[pText[i]].AdvanceX - d_chars[pText[i]].OffsetX * 2))
				pTexWidth += d_chars[pText[i]].Width;
			else
				pTexWidth += d_chars[pText[i]].AdvanceX - d_chars[pText[i]].OffsetX * 2;
		}

		// Create an empty texture for the new text

		D3DSURFACE_DESC desc;
		d_charsetTexture->GetLevelDesc(0, &desc);	// Get description to get format
		hRes = D3DXCreateTexture(RenderMan::getRenderDevice(), pTexWidth, pTexHeight, D3DX_DEFAULT, 0, desc.Format, D3DPOOL_DEFAULT, &pTexture);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create font texture.");
			return false;
		}

		// Get surfaces from textures

		LPDIRECT3DSURFACE9 surfSrc;
		hRes = d_charsetTexture->GetSurfaceLevel(0, &surfSrc);
		if (hRes != D3D_OK)
		{
			echo("ERROR: Can't get surface level for charset texture.");
			return false;
		}
		LPDIRECT3DSURFACE9 surfDest;
		hRes = pTexture->GetSurfaceLevel(0, &surfDest);
		if (hRes != D3D_OK)
		{
			echo("ERROR: Can't get surface level for charset texture.");
			return false;
		}

		// Draw text symbol by symbol

		RECT rectSrc;
		POINT curPos;
		POINT curPosOffset;
		curPos.x = 0;
		curPos.y = 0;
		pCharOffsets.resize(pText.size() + 1);
		pCharOffsets[0] = 0;
		for (unsigned int i = 0; i < pText.size(); ++i)
		{
			rectSrc.left = d_chars[pText[i]].X;
			rectSrc.right = d_chars[pText[i]].X + d_chars[pText[i]].Width;
			rectSrc.top = d_chars[pText[i]].Y;
			rectSrc.bottom = d_chars[pText[i]].Y + d_chars[pText[i]].Height;

			curPosOffset.x = curPos.x;// +m_chars[pText[i]].OffsetX;
			curPosOffset.y = curPos.y + d_chars[pText[i]].OffsetY;
			hRes = RenderMan::getRenderDevice()->UpdateSurface(surfSrc, &rectSrc, surfDest, &curPosOffset);
			if (hRes != D3D_OK)
			{
				echo("ERROR: Can't update surface.");
				return false;
			}

			curPos.x += d_chars[pText[i]].AdvanceX - d_chars[pText[i]].OffsetX * 2;
			pCharOffsets[i + 1] = curPos.x;
		}

		return true;
	}

  bool RBitmapFont::parseFntFile(const std::string& pFntPath)
	{
		LOG("BFont::parseFntFile()");
		int res;

		std::vector<BitmapChar>().swap(d_chars);

		const int tmpLength = 256;
		int iTmp;
		char cTmp[tmpLength];

		std::ifstream f(pFntPath);
		if (!f.is_open())
		{
			echo("ERROR: Can't find font file: \"", pFntPath, "\".");
			return false;
		}

		std::string line;
		std::getline(f, line);

		// Get line height and base
		std::getline(f, line);
		res = sscanf_s(line.c_str(), "common lineHeight=%d base=%d", &d_lineHeight, &d_lineBase);
		if (res != 2)
		{
			echo("ERROR: Can't parse .fnt file: line with line height.");
			return false;
		}

		// Get texture path
		std::getline(f, line);
		res = sscanf_s(line.c_str(), "page id=%d file=\"%s\"", &iTmp, cTmp, tmpLength);
		if (res != 2)
		{
			echo("ERROR: Can't parse .fnt file: line with filename.");
			return false;
		}

		d_charsetPath = std::string(cTmp);
		if (d_charsetPath[d_charsetPath.size() - 1] == '\"')
		{
			// Because we can't parse only filename without stupid enclosing \" symbols
			d_charsetPath.erase(d_charsetPath.size() - 1);
		}

		std::getline(f, line);

		int charCount = 0;
		res = sscanf_s(line.c_str(), "chars count=%d", &charCount);
		if (res != 1)
		{
			echo("ERROR: Can't parse .fnt file: line with chars count.");
			return false;
		}
		d_chars.reserve(charCount < 100 ? 100 : charCount);

		for (int i = 0; i < charCount; ++i)
		{
			int id, x, y, w, h, ox, oy, ax;
			std::getline(f, line);
			res = sscanf_s(line.c_str(), "char id=%d    x=%d    y=%d    width=%d     height=%d     xoffset=%d     yoffset=%d    xadvance=%d",
						   &id, &x, &y, &w, &h, &ox, &oy, &ax);
			if (res != 8)
			{
				echo("ERROR: Can't parse .fnt file: char line with index: \"", i, "\".");
				return false;
			}
			if (d_chars.size() <= (unsigned int)id)
				d_chars.resize(id + 1);

			d_chars[id].Id = id;
			d_chars[id].X = x;
			d_chars[id].Y = y;
			d_chars[id].Width = w;
			d_chars[id].Height = h;
			d_chars[id].OffsetX = ox;
			d_chars[id].OffsetY = oy;
			d_chars[id].AdvanceX = ax;
		}

		f.close();

		return true;
	}

} // Doh3d
