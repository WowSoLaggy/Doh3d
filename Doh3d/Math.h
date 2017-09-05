#pragma once


namespace Doh3d
{

  std::string toStr2(float pValue);
  std::string toStr2(double pValue);


  template <typename T>
  T clamp(T pValue, T pMinValue, T pMaxValue)
  {
    return pValue < pMinValue ? pMinValue : pValue > pMaxValue ? pMaxValue : pValue;
  }


  int sign(int value);
  float sign(float value);

} // ns Doh3d
