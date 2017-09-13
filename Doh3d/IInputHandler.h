#pragma once


namespace Doh3d
{

using Key = int;


enum class MouseButton : int
{
  Left,
  Right,

  End
};


class IInputHandler
{
public:

  virtual bool onMouseMove(bool& i_handled) { i_handled = false; return true; }
  virtual bool onMouseDown(MouseButton i_button, bool& i_handled) { i_handled = false; return true; }
  virtual bool onMouseUp(MouseButton i_button, bool& i_handled) { i_handled = false; return true; }

  virtual bool onKeyPressed(Key i_key) { return true; }
  virtual bool onKeyDown(Key i_key) { return true; }
  virtual bool onKeyUp(Key i_key) { return true; }

};

} // ns Doh3d
