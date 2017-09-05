#pragma once


namespace Doh3d
{

  class Vector2F;

  class Vector2I
  {
  public:

    Vector2I();
    Vector2I(int i_x, int i_y);
    Vector2I(float i_x, float i_y);
    Vector2I(const Vector2F& i_other);

    int x;
    int y;

    float lengthSq() { return (float)(x * x + y * y); }
    float length() { return std::sqrt(lengthSq()); }


    // Operators

    Vector2I operator+() const;
    Vector2I operator-() const;

    Vector2I operator+(const Vector2I& i_other) const;
    Vector2I operator+=(const Vector2I& i_other);
    Vector2I operator-(const Vector2I& i_other) const;
    Vector2I operator-=(const Vector2I& i_other);

    Vector2I operator*(float i_right) const;
    Vector2I operator*=(float i_right);
    Vector2I operator/(float i_right) const;
    Vector2I operator/=(float i_right);

  public:

    static Vector2I zero() { return { 0, 0 }; }
    static Vector2I identity() { return { 1, 1 }; }

  };

} // ns Doh3d
