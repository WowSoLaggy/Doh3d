#include "Doh3d.h"
#include "AnimationController.h"


namespace Doh3d
{

	AnimationController::AnimationController()
	{
		m_animationSet = nullptr;
		m_currentAnimation = nullptr;
		m_currentFrame = 0;
	}


	void AnimationController::Update(float pDeltaTime)
	{
		if (!m_currentAnimation || m_repeats == 0)
			return;

		m_animationTime += pDeltaTime;
		while (m_animationTime >= m_currentAnimation->Interval)
		{
			AdvanceFrame();
			m_animationTime -= m_currentAnimation->Interval;
		}
	}


	bool AnimationController::IsAnimationExist(const std::string& pAnimationName) const
	{
		return (HasAnimationSet() && std::find_if(m_animationSet->Animations.begin(), m_animationSet->Animations.end(),
												  [&](const auto& anim) { return anim.Name == pAnimationName; }) != m_animationSet->Animations.end());
	}

	bool AnimationController::PlayAnimation(const std::string& pAnimationName, int pRepeats)
	{
		if (!HasAnimationSet())
			return false;

		auto& it = std::find_if(m_animationSet->Animations.begin(), m_animationSet->Animations.end(),
					 [&](const auto& anim) { return anim.Name == pAnimationName; });
		if (it == m_animationSet->Animations.end() || &(*it) == nullptr)
			return false;

		m_currentAnimation = &(*it);
		m_currentFrame = m_currentAnimation->BeginFrame - 1;
		m_repeats = pRepeats;
		m_animationTime = 0;

		return true;
	}

	void AnimationController::StopAnimation(bool pReset)
	{
		m_currentAnimation = nullptr;
		if (pReset)
			ResetAnimation();
	}

	void AnimationController::ResetAnimation()
	{
		m_currentFrame = m_currentAnimation != nullptr ? m_currentAnimation->BeginFrame - 1 : 0;
	}


	void AnimationController::AdvanceFrame()
	{
		if (!m_currentAnimation)
			return;

		if (m_currentFrame >= m_currentAnimation->EndFrame - 1)
		{
			if (m_repeats != -1 && --m_repeats == 0)
				return;
			m_currentFrame = m_currentAnimation->BeginFrame - 1;
		}
		else
			++m_currentFrame;
	}

} // Doh3d
