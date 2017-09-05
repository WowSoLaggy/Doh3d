#pragma once


namespace Doh3d
{

  class IControlable
  {
  public:

    virtual void goUpBegin() { }
    virtual void goRightBegin() { }
    virtual void goDownBegin() { }
    virtual void goLeftBegin() { }

    virtual void goUpEnd() { }
    virtual void goRightEnd() { }
    virtual void goDownEnd() { }
    virtual void goLeftEnd() { }

  };

} // ns Doh3d
