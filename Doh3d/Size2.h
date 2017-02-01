#pragma once

#ifndef INC_DOH3D_SIZE2_H
#define INC_DOH3D_SIZE2_H


namespace Doh3d
{

  class Size2
  {
  public:

    Size2();
    Size2(int pX, int pY);
    Size2(float pX, float pY);

    virtual ~Size2() { }


    int& x() { return d_x; }
    const int& x() const { return d_x; }

    int& y() { return d_y; }
    const int& y() const { return d_y; }


    // Operators

    Size2 operator+(const Size2& pSize) const;
    Size2 operator-(const Size2& pSize) const;
    Size2 operator/(int pRight) const;

  private:

    int d_x;
    int d_y;

  };

} // ns Doh3d


#endif // INC_DOH3D_SIZE2_H
