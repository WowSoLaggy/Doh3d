#pragma once

#ifndef INC_DOH3D_MATH_H
#define INC_DOH3D_MATH_H


namespace Doh3d
{

  std::string toStr2(float pValue);
  std::string toStr2(double pValue);


  template <typename T>
  T clamp(T pValue, T pMinValue, T pMaxValue)
  {
    return pValue < pMinValue ? pMinValue : pValue > pMaxValue ? pMaxValue : pValue;
  }

} // ns Doh3d


#endif // INC_DOH3D_MATH_H
