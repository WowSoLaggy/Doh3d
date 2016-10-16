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


	struct InputPars
	{
		InputPars()
			: InputPars(0, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) { }

		InputPars(float pMouseSensX, float pMouseSensY,
				  Input_MouseMove pOnMouseMove, Input_MouseDown pOnMouseDown, Input_MouseUp pOnMouseUp,
				  Input_KeyPressed pOnKeyPressed, Input_KeyDown pOnKeyDown, Input_KeyUp pOnKeyUp)
			: MouseSensX(pMouseSensX), MouseSensY(pMouseSensY),
			OnMouseMove(pOnMouseMove), OnMouseDown(pOnMouseDown), OnMouseUp(pOnMouseUp),
			OnKeyPressed(pOnKeyPressed), OnKeyDown(pOnKeyDown), OnKeyUp(pOnKeyUp)
			{ }

		float MouseSensX;				// Mouse cursor X-axis sensitivity
		float MouseSensY;				// Mouse cursor Y-axis sensitivity

		// Input handlers

		Input_MouseMove OnMouseMove;	// Event that occurs when the mouse is moved
		Input_MouseDown OnMouseDown;	// Event that occurs when the mouse button is pressed
		Input_MouseUp OnMouseUp;		// Event that occurs when the mouse button is released

		Input_KeyPressed OnKeyPressed;	// Event that occurs when the key is pressed and released
		Input_KeyDown OnKeyDown;		// Event that occurs when the key is pressed
		Input_KeyUp OnKeyUp;			// Event that occurs when the key is released

	};

} // ns Doh3d


#endif // INC_DOH3D_INPUTPARS_H
