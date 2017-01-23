#pragma once

#ifndef INC_DOH3D_TEXTURE_H
#define INC_DOH3D_TEXTURE_H


#include "AlphaMap.h"


namespace Doh3d
{

	class Texture
	{
	public:

		Texture(const std::string& pFilePath, const D3DXVECTOR2& pSize, int pTotalFrames, bool pAlphaCheck)
			: m_filePath(pFilePath), m_size(pSize), m_size2(pSize / 2), m_totalFrames(pTotalFrames), m_texture(nullptr), m_alphaCheck(pAlphaCheck) { }


		const std::string& GetFilePath() const { return m_filePath; }
		LPDIRECT3DTEXTURE9 Get() { return m_texture; }
		const D3DXVECTOR2& GetSize() const { return m_size; }
		const D3DXVECTOR2& GetSize2() const { return m_size2; }

		RECT GetFrame(int pFrameNumber);


		bool Load();
    bool Unload();


		bool HitTest(int pX, int pY, int pFrame) const;
		bool HitTest(float pX, float pY, int pFrame) const;
		bool HitTest(const D3DXVECTOR2& pCoords, int pFrame) const;
		bool HitTest(const D3DXVECTOR3& pCoords, int pFrame) const;

	private:

		std::string m_filePath;
		D3DXVECTOR2 m_size;
		D3DXVECTOR2 m_size2;
		int m_totalFrames;
		bool m_alphaCheck;

		AlphaMap m_alphaMap;
		LPDIRECT3DTEXTURE9 m_texture;

	};

} // Doh3d


#endif // INC_DOH3D_TEXTURE_H
