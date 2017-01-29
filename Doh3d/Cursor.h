#pragma once

#ifndef INC_DOH3D_CURSOR_H
#define INC_DOH3D_CURSOR_H


#include "Sprite.h"


namespace Doh3d
{

	class Cursor
	{
	public:

		static bool setCursorTexture(const std::string& pTextureName);

		static bool draw(Sprite& pSprite);

	private:

		static int d_ti;
		static D3DXMATRIX d_identityMatrix;

	};

} // ns Doh3d


#endif // INC_DOH3D_CURSOR_H
