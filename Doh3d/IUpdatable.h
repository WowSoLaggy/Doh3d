#pragma once


namespace Doh3d
{

  class IUpdatable
  {
  public:

    virtual ~IUpdatable() { }

    virtual bool update(float i_dt) PURE;

  };

} // ns Doh3d
