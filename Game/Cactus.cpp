#include "Cactus.h"

void Cactus::Render()
{
	animationSet->at(CACTUS_ANIMATION)->Render(1, x, y);
}
