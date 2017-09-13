#pragma once


namespace Doh3d
{

  class Animation
  {
  public:

    Animation(const std::string& i_name, int i_beginFrame, int i_endFrame, float i_interval)
      : name(i_name)
      , beginFrame(i_beginFrame)
      , endFrame(i_endFrame)
      , interval(i_interval)
    {
    }

    std::string name;
    int beginFrame;
    int endFrame;
    float interval;

  };

} // ns Doh3d
