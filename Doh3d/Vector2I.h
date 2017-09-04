#pragma once


namespace Doh3d
{

  class Vector2I
  {
  public:

    Vector2I();
    Vector2I(int i_x, int i_y);
    Vector2I(float i_x, float i_y);

    int x;
    int y;


    // Operators

    Vector2I operator+(const Vector2I& i_other) const;
    Vector2I operator+=(const Vector2I& i_other);
    Vector2I operator-(const Vector2I& i_other) const;
    Vector2I operator-=(const Vector2I& i_other);

  public:

    static Vector2I zero() { return { 0, 0 }; }
    static Vector2I identity() { return { 1, 1 }; }

  };

} // ns Doh3d
