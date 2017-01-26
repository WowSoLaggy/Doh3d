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


		LPD3DXSPRITE get() const { return d_sprite; }


		bool begin();
    bool end();


    bool load();
    bool unload();
    bool reload();

	private:

		mutable LPD3DXSPRITE d_sprite;

	};

} // ns Doh3d


#endif // INC_DOH3D_SPRITE_H
