#pragma once

#ifndef DOH3D_SPRITE_H
#define DOH3D_SPRITE_H


namespace Doh3d
{

	class Sprite
	{
	public:

		Sprite()
			: m_sprite(nullptr) { }


		LPD3DXSPRITE Get() const { return m_sprite; }


		ErrCode3d Begin();
		ErrCode3d End();


		ErrCode3d Load();
		ErrCode3d Unload();
		ErrCode3d Reload();

	private:

		mutable LPD3DXSPRITE m_sprite;

	};

} // ns Doh3d


#endif // DOH3D_SPRITE_H
