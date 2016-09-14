#pragma once

#ifndef DOH3D_ERRCODES3D_H
#define DOH3D_ERRCODES3D_H


namespace Doh3d
{

	namespace Doh3dErrCodes
	{

		enum ErrCode3d
		{
			err3d_noErr = 0,
			err3d_cantAllocMemory,
			err3d_invalidArguments,
			err3d_cantCreateWindow,
			err3d_cantCreateDirectX,
			err3d_cantCreateRenderDevice,
			err3d_cantBeginScene,
			err3d_cantEndScene,
			err3d_cantCreateDirectInput,
			err3d_cantCreateInputDevice,
			err3d_cantAcquireInputDevice,
			err3d_cantCreateThread,
			err3d_cantCreateSprite,
			err3d_sceneAlreadyLoaded,
			err3d_sceneNotLoaded,
			err3d_unrecognizedScriptEvent,
			err3d_cantDrawSprite,
			err3d_cantLoadTexture,
			err3d_cantCreateTextureForEmptyText,
			err3d_cantCreateTexture,
			err3d_cantGetSurfaceFromTexture,
			err3d_cantUpdateSurface,
			err3d_cantFindFontFile,
			err3d_cantParseFontFile,
			err3d_noTexturesFolder,
			err3d_noFontsFolder,
			err3d_textureNotFound,
			err3d_cantBeginSprite,
			err3d_cantEndSprite,
			err3d_cantDrawText,
			err3d_cantCursorTextureIsNotSet,
			err3d_textureNotSet,
			err3d_invalidTextureDir,

			err3d_end,
		};

	} // Doh3dErrCodes

} // ns Doh3d


#endif // DOH3D_ERRCODES3D_H
