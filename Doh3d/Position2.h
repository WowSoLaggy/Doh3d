#pragma once

#ifndef INC_DOH3D_POSITION2_H
#define INC_DOH3D_POSITION2_H


namespace Doh3d
{

  class Size2;


  class Position2
  {
  public:

    Position2();
    Position2(int pX, int pY);
    Position2(float pX, float pY);
    Position2(const D3DXVECTOR2& pVector2);
    Position2(const D3DXVECTOR3& pVector3);

    virtual ~Position2() { }


    int x() const { return (int)d_rawVector.x; }
    int y() const { return (int)d_rawVector.y; }


    D3DXVECTOR3& rawVector() { return d_rawVector; }
    const D3DXVECTOR3& rawVector() const { return d_rawVector; }

    D3DXVECTOR3* rawVectorPtr() { return &d_rawVector; }
    const D3DXVECTOR3* rawVectorPtr() const { return &d_rawVector; }


    // Operators

    Position2 operator+(const Position2& pPosition) const;
    Position2 operator-(const Position2& pPosition) const;

    Position2 operator+(const Size2& pSize) const;
    Position2 operator-(const Size2& pSize) const;


    static Position2 zero() { return Position2(0, 0); }

  private:

    D3DXVECTOR3 d_rawVector;

  };

} // ns Doh3d


#endif // INC_DOH3D_POSITION2_H
