#include "PrecompiledHeader.h"
#include "IAnimated.h"


namespace Doh3d
{

IAnimated::IAnimated()
  : d_currentFrame(0)
{
}


bool IAnimated::updateAnimation(float i_dt)
{
  if (!d_currentAnimation || d_repeats == 0)
    return true;

  d_animationTime += i_dt;
  while (d_animationTime >= d_currentAnimation->interval)
  {
    if (!advanceFrame())
      return false;
    d_animationTime -= d_currentAnimation->interval;
  }

  return true;
}

bool IAnimated::playAnimation(const std::string& i_animationName, int i_repeatNum)
{
  LOG(__FUNCTION__);

  const auto& animationSet = getAnimationSet();

  auto& it = std::find_if(animationSet.animations.cbegin(), animationSet.animations.cend(),
                          [&](const auto& i_animation) { return i_animation.name == i_animationName; });
  if (it == animationSet.animations.cend())
  {
    echo("ERROR: Can't find animation: \"", i_animationName, "\".");
    return false;
  }

  d_currentAnimation.reset(new Animation(*it));
  d_currentFrame = d_currentAnimation->beginFrame - 1;
  d_repeats = i_repeatNum;
  d_animationTime = 0;
  d_directOrder = (d_currentAnimation->endFrame >= d_currentAnimation->beginFrame);

  return true;
}


bool IAnimated::advanceFrame()
{
  LOG(__FUNCTION__);

  if (!d_currentAnimation)
  {
    echo("ERROR: No current animation to advance.");
    return false;
  }

  if (d_directOrder)
  {
    if (d_currentFrame >= d_currentAnimation->endFrame - 1)
    {
      if (d_repeats != -1 && --d_repeats == 0)
        return true;
      d_currentFrame = d_currentAnimation->beginFrame - 1;
    }
    else
      ++d_currentFrame;
  }
  else
  {
    if (d_currentFrame <= d_currentAnimation->endFrame - 1)
    {
      if (d_repeats != -1 && --d_repeats == 0)
        return true;
      d_currentFrame = d_currentAnimation->beginFrame - 1;
    }
    else
      --d_currentFrame;
  }

  return true;
}

} // ns Doh3d
