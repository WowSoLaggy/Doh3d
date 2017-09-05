#pragma once


namespace Doh3d
{

	class RenderPars
	{
  public:

		RenderPars()
			: d_resolutionWidth(800), d_resolutionHeight(600), d_windowed(true), d_hasCaption(false), d_fullScreenRefreshRate(60) { }

		RenderPars(int pResolutionWidth, int pResolutionHeight, bool pWindowed, bool pWndCaption, int pFullScreenRefreshRate)
			: d_resolutionWidth(pResolutionWidth), d_resolutionHeight(pResolutionHeight), d_windowed(pWindowed), d_hasCaption(pWndCaption), d_fullScreenRefreshRate(pFullScreenRefreshRate) { }


    int& resolutionWidth() { return d_resolutionWidth; }
    const int& resolutionWidth() const { return d_resolutionWidth; }

    int& resolutionHeight() { return d_resolutionHeight; }
    const int& resolutionHeight() const { return d_resolutionHeight; }

    bool& windowed() { return d_windowed; }
    const bool& windowed() const { return d_windowed; }

    bool& hasBorder() { return d_hasCaption; }
    const bool& hasBorder() const { return d_hasCaption; }

    int& fullScreenRefreshRate() { return d_fullScreenRefreshRate; }
    const int& fullScreenRefreshRate() const { return d_fullScreenRefreshRate; }


  private:

		int d_resolutionWidth;		    // Resolution X-dimension
		int d_resolutionHeight;		    // Resolution Y-dimension
		bool d_windowed;				      // Indicates whether the game should be launched in window (true) or fullscreen (false)
		bool d_hasCaption;  	        // Indicates whether the game window should have border and caption. Works only if Windowed == true
		int d_fullScreenRefreshRate;  // Screen refresh rate while fullscreened
	};

} // ns Doh3d
