#pragma once

#ifndef INC_DOH3D_ANIMATION_H
#define INC_DOH3D_ANIMATION_H


namespace Doh3d
{

	class Animation
	{
	public:

		std::string Name;
		int BeginFrame;
		int EndFrame;
		float Interval;

	};

} // ns Doh3d


#endif // INC_DOH3D_ANIMATION_H
