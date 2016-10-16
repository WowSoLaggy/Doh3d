#pragma once

#ifndef INC_DOH3D_CURSOR_H
#define INC_DOH3D_CURSOR_H


#include "Sprite.h"


namespace Doh3d
{

	class Cursor
	{
	public:

		static ErrCode3d SetCursorTexture(const std::string& pTextureName);

		static ErrCode3d Draw(const Sprite& pSprite);

	private:

		static int m_ti;
		static D3DXMATRIX m_identityMatrix;

	};

} // ns Doh3d


#endif // INC_DOH3D_CURSOR_H
