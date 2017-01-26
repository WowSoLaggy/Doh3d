#include "Doh3d.h"
#include "AnimationController.h"


namespace Doh3d
{

  AnimationController::AnimationController()
  {
    d_animationSet = nullptr;
    d_currentAnimation = nullptr;
    d_currentFrame = 0;
  }


  void AnimationController::update(float pDeltaTime)
  {
    if (!d_currentAnimation || d_repeats == 0)
      return;

    d_animationTime += pDeltaTime;
    while (d_animationTime >= d_currentAnimation->Interval)
    {
      advanceFrame();
      d_animationTime -= d_currentAnimation->Interval;
    }
  }


  bool AnimationController::isAnimationExist(const std::string& pAnimationName) const
  {
    return (hasAnimationSet() && std::find_if(d_animationSet->Animations.begin(), d_animationSet->Animations.end(),
                                              [&](const auto& anim) { return anim.Name == pAnimationName; }) != d_animationSet->Animations.end());
  }

  bool AnimationController::playAnimation(const std::string& pAnimationName, int pRepeats)
  {
    if (!hasAnimationSet())
      return false;

    auto& it = std::find_if(d_animationSet->Animations.begin(), d_animationSet->Animations.end(),
                            [&](const auto& anim) { return anim.Name == pAnimationName; });
    if (it == d_animationSet->Animations.end() || &(*it) == nullptr)
      return false;

    d_currentAnimation = &(*it);
    d_currentFrame = d_currentAnimation->BeginFrame - 1;
    d_repeats = pRepeats;
    d_animationTime = 0;
    d_directOrder = (d_currentAnimation->EndFrame >= d_currentAnimation->BeginFrame);

    return true;
  }

  void AnimationController::stopAnimation(bool pReset)
  {
    d_currentAnimation = nullptr;
    if (pReset)
      resetAnimation();
  }

  void AnimationController::resetAnimation()
  {
    d_currentFrame = d_currentAnimation != nullptr ? d_currentAnimation->BeginFrame - 1 : 0;
  }


  void AnimationController::advanceFrame()
  {
    if (!d_currentAnimation)
      return;

    if (d_directOrder)
    {
      if (d_currentFrame >= d_currentAnimation->EndFrame - 1)
      {
        if (d_repeats != -1 && --d_repeats == 0)
          return;
        d_currentFrame = d_currentAnimation->BeginFrame - 1;
      }
      else
        ++d_currentFrame;
    }
    else
    {
      if (d_currentFrame <= d_currentAnimation->EndFrame - 1)
      {
        if (d_repeats != -1 && --d_repeats == 0)
          return;
        d_currentFrame = d_currentAnimation->BeginFrame - 1;
      }
      else
        --d_currentFrame;
    }
  }

} // Doh3d
