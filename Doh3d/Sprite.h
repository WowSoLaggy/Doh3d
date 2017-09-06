#pragma once

#include "IPositioned2I.h"
#include "Vector2F.h"


namespace Doh3d
{

	class Sprite final
	{
	public:

    Sprite();


		bool begin();
    bool end();


    const Position2I& getTranslation() const { return d_translation; }
    void setTranslation(const Position2I& i_translation);
    void resetTranslation();

    const Vector2F& getScale() const { return d_scale; }
    void setScale(const Vector2F& i_scale);
    void resetScale();

    void resetTransform();

    
    // TODO: change pars types to some typedef
    bool draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT *pSrcRect, CONST D3DXVECTOR3 *pCenter, const Position2I& pPosition, D3DCOLOR Color);


    bool load();
    bool unload();
    bool reload();

	private:

		LPD3DXSPRITE d_sprite;

    Position2I d_translation;
    Vector2F d_scale;

    void updateTransform();

	};

} // ns Doh3d
