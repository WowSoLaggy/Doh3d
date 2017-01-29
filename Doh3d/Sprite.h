#pragma once

#ifndef INC_DOH3D_SPRITE_H
#define INC_DOH3D_SPRITE_H


namespace Doh3d
{

	class Sprite
	{
	public:

		Sprite()
			: d_sprite(nullptr) { }


		bool begin();
    bool end();


    // TODO: change par type to some typedef
    void setTransform(const D3DXMATRIX* pTransform);

    // TODO: change return type to bool
    // TODO: change pars types to some typedef
    HRESULT draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT *pSrcRect, CONST D3DXVECTOR3 *pCenter, CONST D3DXVECTOR3 *pPosition, D3DCOLOR Color);


    bool load();
    bool unload();
    bool reload();

	private:

		mutable LPD3DXSPRITE d_sprite;

	};

} // ns Doh3d


#endif // INC_DOH3D_SPRITE_H
