#pragma once

#ifndef INC_DOH3D_INPUTPARS_H
#define INC_DOH3D_INPUTPARS_H


namespace Doh3d
{

	typedef std::function<void()> Input_MouseMove;
	typedef std::function<void(int pButton)> Input_MouseDown;
	typedef std::function<void(int pButton)> Input_MouseUp;

	typedef std::function<void(int pKey)> Input_KeyPressed;
	typedef std::function<void(int pKey)> Input_KeyDown;
	typedef std::function<void(int pKey)> Input_KeyUp;


	class InputPars
	{

  public:

		InputPars()
			: InputPars(0, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) { }

		InputPars(float pMouseSensX, float pMouseSensY,
				  Input_MouseMove pOnMouseMove, Input_MouseDown pOnMouseDown, Input_MouseUp pOnMouseUp,
				  Input_KeyPressed pOnKeyPressed, Input_KeyDown pOnKeyDown, Input_KeyUp pOnKeyUp)
			: d_mouseSensX(pMouseSensX), d_mouseSensY(pMouseSensY),
			d_onMouseMove(pOnMouseMove), d_onMouseDown(pOnMouseDown), d_onMouseUp(pOnMouseUp),
			d_onKeyPressed(pOnKeyPressed), d_onKeyDown(pOnKeyDown), d_onKeyUp(pOnKeyUp)
			{ }

    
    float& mouseSensX() { return d_mouseSensX; }
    const float& mouseSensX() const { return d_mouseSensX; }

    float& mouseSensY() { return d_mouseSensY; }
    const float& mouseSensY() const { return d_mouseSensY; }

    // Input handlers

    Input_MouseMove& onMouseMove() { return d_onMouseMove; }
    Input_MouseDown& onMouseDown() { return d_onMouseDown; }
    Input_MouseUp& onMouseUp() { return d_onMouseUp; }

    Input_KeyPressed& onKeyPressed() { return d_onKeyPressed; }
    Input_KeyDown& onKeyDown() { return d_onKeyDown; }
    Input_KeyUp& onKeyUp() { return d_onKeyUp; }


  private:

		float d_mouseSensX;				      // Mouse cursor X-axis sensitivity
		float d_mouseSensY;				      // Mouse cursor Y-axis sensitivity

		// Input handlers

		Input_MouseMove d_onMouseMove;	  // Event that occurs when the mouse is moved
		Input_MouseDown d_onMouseDown;	  // Event that occurs when the mouse button is pressed
		Input_MouseUp d_onMouseUp;		    // Event that occurs when the mouse button is released

		Input_KeyPressed d_onKeyPressed;	// Event that occurs when the key is pressed and released
		Input_KeyDown d_onKeyDown;		    // Event that occurs when the key is pressed
		Input_KeyUp d_onKeyUp;			      // Event that occurs when the key is released

	};

} // ns Doh3d


#endif // INC_DOH3D_INPUTPARS_H
