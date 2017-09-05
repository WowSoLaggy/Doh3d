#pragma once


namespace Doh3d
{

	class Viewport
	{

  public:

    float left() const { return d_positionX - d_width2; }
    float top() const { return d_positionY - d_height2; }
    float right() const { return d_positionX + d_width2; }
    float bottom() const { return d_positionY + d_height2; }

  private:

		float d_positionX;
		float d_positionY;

		float d_width2;
		float d_height2;
		
	};

} // ns Doh3d
