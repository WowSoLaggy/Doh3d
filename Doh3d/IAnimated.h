#pragma once

#include "AnimationSet.h"


namespace Doh3d
{

class IAnimated
{
public:

  IAnimated();

  
  int getCurrentFrame() const { return d_currentFrame; }

  virtual const AnimationSet& getAnimationSet() const PURE;

  bool updateAnimation(float i_dt);
  bool playAnimation(const std::string& i_animationName, int i_repeatNum); //< -1 for infinite

private:

  std::unique_ptr<Animation> d_currentAnimation;
  int d_currentFrame;
  int d_repeats;
  float d_animationTime;
  bool d_directOrder;

  bool advanceFrame();

};

} // ns Doh3d
