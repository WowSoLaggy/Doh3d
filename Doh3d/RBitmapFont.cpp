#include "Doh3d.h"
#include "RBitmapFont.h"

#include "RenderMan.h"
#include "ResourceMan.h"


namespace Doh3d
{

	RBitmapFont::RBitmapFont(const std::string& pFontName)
	{
		m_fontName = pFontName;
		m_charsetPath = "";
		m_charsetTexture = nullptr;
	}

	RBitmapFont::~RBitmapFont()
	{
	}

  bool RBitmapFont::Load()
	{
		LOG("BFont::Load()");
		int hRes;

		// Parse .fnt file

		std::string fntPath = "";
		fntPath.append(ResourceMan::GetFontDir()).append(m_fontName);
		if (!ParseFntFile(fntPath))
		{
			echo("ERROR: Can't parse .fnt file: \"", fntPath, "\".");
			return false;
		}

		m_charsetPath.insert(0, ResourceMan::GetFontDir());

		// Read texture

		hRes = D3DXCreateTextureFromFileEx(RenderMan::GetRenderDevice(), m_charsetPath.c_str(),
										   D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_SYSTEMMEM, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_charsetTexture);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create texture for font: \"", m_fontName, "\".");
			return false;
		}

		return true;
	}

  bool RBitmapFont::Unload()
	{
		if (m_charsetTexture != nullptr)
		{
			m_charsetTexture->Release();
			m_charsetTexture = nullptr;
		}

		std::vector<BitmapChar>().swap(m_chars);

		return true;
	}

  bool RBitmapFont::GetFontTexture(const std::string& pText, LPDIRECT3DTEXTURE9& pTexture, int& pTexWidth, int& pTexHeight, std::vector<int>& pCharOffsets)
	{
		LOG("BFont::GetFontTexture()");
		int hRes;

		if (pText.empty())
		{
			pTexture = nullptr;
			return false;
		}

		// Get overall text width and height

		pTexWidth = 0;
		pTexHeight = m_lineHeight;

		for (unsigned int i = 0; i < pText.size(); ++i)
		{
			if (m_chars[pText[i]].Width > (m_chars[pText[i]].AdvanceX - m_chars[pText[i]].OffsetX * 2))
				pTexWidth += m_chars[pText[i]].Width;
			else
				pTexWidth += m_chars[pText[i]].AdvanceX - m_chars[pText[i]].OffsetX * 2;
		}

		// Create an empty texture for the new text

		D3DSURFACE_DESC desc;
		m_charsetTexture->GetLevelDesc(0, &desc);	// Get description to get format
		hRes = D3DXCreateTexture(RenderMan::GetRenderDevice(), pTexWidth, pTexHeight, D3DX_DEFAULT, 0, desc.Format, D3DPOOL_DEFAULT, &pTexture);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't create font texture.");
			return false;
		}

		// Get surfaces from textures

		LPDIRECT3DSURFACE9 surfSrc;
		hRes = m_charsetTexture->GetSurfaceLevel(0, &surfSrc);
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
			rectSrc.left = m_chars[pText[i]].X;
			rectSrc.right = m_chars[pText[i]].X + m_chars[pText[i]].Width;
			rectSrc.top = m_chars[pText[i]].Y;
			rectSrc.bottom = m_chars[pText[i]].Y + m_chars[pText[i]].Height;

			curPosOffset.x = curPos.x;// +m_chars[pText[i]].OffsetX;
			curPosOffset.y = curPos.y + m_chars[pText[i]].OffsetY;
			hRes = RenderMan::GetRenderDevice()->UpdateSurface(surfSrc, &rectSrc, surfDest, &curPosOffset);
			if (hRes != D3D_OK)
			{
				echo("ERROR: Can't update surface.");
				return false;
			}

			curPos.x += m_chars[pText[i]].AdvanceX - m_chars[pText[i]].OffsetX * 2;
			pCharOffsets[i + 1] = curPos.x;
		}

		return true;
	}

  bool RBitmapFont::ParseFntFile(const std::string& pFntPath)
	{
		LOG("BFont::ParseFntFile()");
		int res;

		std::vector<BitmapChar>().swap(m_chars);

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
		res = sscanf_s(line.c_str(), "common lineHeight=%d base=%d", &m_lineHeight, &m_lineBase);
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

		m_charsetPath = std::string(cTmp);
		if (m_charsetPath[m_charsetPath.size() - 1] == '\"')
		{
			// Because we can't parse only filename without stupid enclosing \" symbols
			m_charsetPath.erase(m_charsetPath.size() - 1);
		}

		std::getline(f, line);

		int charCount = 0;
		res = sscanf_s(line.c_str(), "chars count=%d", &charCount);
		if (res != 1)
		{
			echo("ERROR: Can't parse .fnt file: line with chars count.");
			return false;
		}
		m_chars.reserve(charCount < 100 ? 100 : charCount);

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
			if (m_chars.size() <= (unsigned int)id)
				m_chars.resize(id + 1);

			m_chars[id].Id = id;
			m_chars[id].X = x;
			m_chars[id].Y = y;
			m_chars[id].Width = w;
			m_chars[id].Height = h;
			m_chars[id].OffsetX = ox;
			m_chars[id].OffsetY = oy;
			m_chars[id].AdvanceX = ax;
		}

		f.close();

		return true;
	}

} // Doh3d
