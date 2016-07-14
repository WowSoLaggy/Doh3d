#pragma once

#ifndef ERRCODES_H
#define ERRCODES_H


namespace Doh3d
{

	enum ErrCode
	{
		err_noErr = 0,
		err_cantAllocMemory,
		err_invalidArguments,
		err_cantCreateWindow,
		err_cantCreateDirectX,
		err_cantCreateRenderDevice,
		err_cantBeginScene,
		err_cantEndScene,
		err_cantCreateDirectInput,
		err_cantCreateInputDevice,
		err_cantAcquireInputDevice,
		err_cantCreateThread,
		err_cantCreateSprite,
		err_sceneAlreadyLoaded,
		err_sceneNotLoaded,
		err_unrecognizedScriptEvent,
		err_cantDrawSprite,
		err_cantLoadTexture,
		err_cantCreateTextureForEmptyText,
		err_cantCreateTexture,
		err_cantGetSurfaceFromTexture,
		err_cantUpdateSurface,
		err_cantFindFontFile,
		err_cantParseFontFile,
		err_noTexturesFolder,
		err_noFontsFolder,
		err_textureNotFound,
		err_cantBeginSprite,
		err_cantEndSprite,
		err_cantDrawText,
		err_cantCursorTextureIsNotSet,
		err_textureNotSet,

		err_end,
	};

} // ns Doh3d


#endif // ERRCODES_H
