#pragma once

#ifndef INC_DOH3D_ANIMATIONCONTROLLER_H
#define INC_DOH3D_ANIMATIONCONTROLLER_H


namespace Doh3d
{

	class AnimationController
	{
	public:

		AnimationController();

		int getCurrentFrame() const { return d_currentFrame; }

		bool hasAnimationSet() const { return d_animationSet != nullptr; }
		void setAnimationSet(const AnimationSet* pAnimationSet) { d_animationSet = pAnimationSet; }

		bool isAnimationExist(const std::string& pAnimationName) const;
		bool playAnimation(const std::string& pAnimationName, int pRepeats); ///< -1 for infinite
		void stopAnimation(bool pReset);
		void resetAnimation(); ///< Resets to the animation.begin_frame or to the 0 if no animation

		void update(float pDeltaTime);

	private:

		const AnimationSet* d_animationSet;
		const Animation* d_currentAnimation;

		int d_currentFrame;
		int d_repeats;
		float d_animationTime;
		bool d_directOrder;

		void advanceFrame();

	};

} // Doh3d


#endif // INC_DOH3D_ANIMATIONCONTROLLER_H
