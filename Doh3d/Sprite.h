#pragma once

#ifndef INC_DOH3D_SPRITE_H
#define INC_DOH3D_SPRITE_H


namespace Doh3d
{

	class Sprite
	{
	public:

		Sprite()
			: m_sprite(nullptr) { }


		LPD3DXSPRITE Get() const { return m_sprite; }


		bool Begin();
    bool End();


    bool Load();
    bool Unload();
    bool Reload();

	private:

		mutable LPD3DXSPRITE m_sprite;

	};

} // ns Doh3d


#endif // INC_DOH3D_SPRITE_H
