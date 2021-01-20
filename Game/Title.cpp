#include "Title.h"
void Title::Render()
{
	animationSet->at(0)->Render(1, x, y);
}