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
			: m_filePath(pFilePath), m_size(pSize), m_totalFrames(pTotalFrames), m_texture(nullptr), m_alphaCheck(pAlphaCheck) { }


		const std::string& GetFilePath() const { return m_filePath; }
		LPDIRECT3DTEXTURE9 Get() { return m_texture; }
		const D3DXVECTOR2& GetSize() const { return m_size; }

		RECT GetFrame(int pFrameNumber);


		ErrCode3d Load();
		ErrCode3d Unload();


		bool HitTest(int pX, int pY) const;
		bool HitTest(float pX, float pY) const;
		bool HitTest(const D3DXVECTOR2& pCoords) const;
		bool HitTest(const D3DXVECTOR3& pCoords) const;

	private:

		std::string m_filePath;
		D3DXVECTOR2 m_size;
		int m_totalFrames;
		bool m_alphaCheck;

		AlphaMap m_alphaMap;
		LPDIRECT3DTEXTURE9 m_texture;

	};

} // Doh3d


#endif // INC_DOH3D_TEXTURE_H
