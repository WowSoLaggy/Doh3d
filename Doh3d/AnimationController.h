#pragma once

#ifndef INC_DOH3D_ANIMATIONCONTROLLER_H
#define INC_DOH3D_ANIMATIONCONTROLLER_H


namespace Doh3d
{

	class AnimationController
	{
	public:

		AnimationController();

		int GetCurrentFrame() const { return m_currentFrame; }

		bool HasAnimationSet() const { return m_animationSet != nullptr; }
		void SetAnimationSet(const AnimationSet* pAnimationSet) { m_animationSet = pAnimationSet; }

		bool IsAnimationExist(const std::string& pAnimationName) const;
		bool PlayAnimation(const std::string& pAnimationName, int pRepeats); ///< -1 for infinite
		void StopAnimation(bool pReset);
		void ResetAnimation(); ///< Resets to the animation.begin_frame or to the 0 if no animation

		void Update(float pDeltaTime);

	private:

		const AnimationSet* m_animationSet;
		const Animation* m_currentAnimation;

		int m_currentFrame;
		int m_repeats;
		float m_animationTime;
		bool m_directOrder;

		void AdvanceFrame();

	};

} // Doh3d


#endif // INC_DOH3D_ANIMATIONCONTROLLER_H
