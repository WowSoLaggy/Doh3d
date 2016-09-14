#pragma once

#ifndef DOH3D_RENDERPARS_H
#define DOH3D_RENDERPARS_H


namespace Doh3d
{

	struct RenderPars
	{
		RenderPars()
			: ResolutionWidth(800), ResolutionHeight(600), Windowed(true), WndCaption(false), FullScreenRefreshRate(60) { }

		RenderPars(int pResolutionWidth, int pResolutionHeight, bool pWindowed, bool pWndCaption, int pFullScreenRefreshRate)
			: ResolutionWidth(pResolutionWidth), ResolutionHeight(pResolutionHeight), Windowed(pWindowed), WndCaption(pWndCaption), FullScreenRefreshRate(pFullScreenRefreshRate) { }

		int ResolutionWidth;		// Resolution X-dimension
		int ResolutionHeight;		// Resolution Y-dimension
		bool Windowed;				// Indicates whether the game should be launched in window (true) or fullscreen (false)
		bool WndCaption;			// Indicates whether the game window should have border and caption. Works only if Windowed == true
		int FullScreenRefreshRate;	// Screen refresh rate while fullscreened
	};

} // ns Doh3d


#endif // DOH3D_RENDERPARS_H
