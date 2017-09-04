#pragma once


namespace Doh3d
{

  class Vector2F
  {
  public:

    Vector2F();
    Vector2F(int i_x, int i_y);
    Vector2F(float i_x, float i_y);

    float x;
    float y;


    // Operators

    Vector2F operator+(const Vector2F& i_other) const;
    Vector2F operator+=(const Vector2F& i_other);
    Vector2F operator-(const Vector2F& i_other) const;
    Vector2F operator-=(const Vector2F& i_other);

    Vector2F operator*(float i_right) const;
    Vector2F operator*=(float i_right);
    Vector2F operator/(float i_right) const;
    Vector2F operator/=(float i_right);

  public:

    static Vector2F zero() { return{ 0, 0 }; }
    static Vector2F identity() { return{ 1, 1 }; }

  };

} // ns Doh3d
