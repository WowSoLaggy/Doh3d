#include "Doh3d.h"
#include "GPanel.h"


namespace Doh3d
{

  bool GPanel::drawSelf(Sprite& pSprite) const
  {

    pSprite.draw();

    return true;
  }

} // ns Doh3d
