#include "PrecompiledHeader.h"
#include "Math.h"


namespace Doh3d
{

  std::string toStr2(float pValue)
  {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << pValue;
    return ss.str();
  }

  std::string toStr2(double pValue)
  {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << pValue;
    return ss.str();
  }


  int sign(int value) { return value >= 0 ? 1 : -1; }
  float sign(float value) { return value >= 0 ? 1.0f : -1.0f; }

} // ns Doh3d
