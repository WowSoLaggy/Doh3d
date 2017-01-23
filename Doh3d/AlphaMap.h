#pragma once

#ifndef INC_DOH3D_ALPHAMAP_H
#define INC_DOH3D_ALPHAMAP_H


namespace Doh3d
{

	class AlphaMap
	{
	public:

		bool Init(bool pAlphaCheck, LPDIRECT3DTEXTURE9 pTexture);

		bool Check(int pX, int pY) const;

	private:

		int m_width;
		int m_height;

		bool m_solid;
		std::vector<bool> m_mask;

	};

} // ns Doh3d


#endif // INC_DOH3D_ALPHAMAP_H
