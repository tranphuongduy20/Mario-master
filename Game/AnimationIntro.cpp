#include <algorithm>
#include "debug.h"
#include "AnimationIntro.h"
#include "Game.h"


AnimationIntro::AnimationIntro(float x, float y) : Entity()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(3));
	this->x = x;
	this->y = y;
}
AnimationIntro* AnimationIntro::instance = NULL;
AnimationIntro* AnimationIntro::GetInstance()
{
	if (instance == NULL)
		instance = new AnimationIntro();
	return instance;
}

void AnimationIntro::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
#pragma endregion
}


void AnimationIntro::Render()
{
#pragma region Khai báo biến
	int ani = -1;
	int alpha = 255;
	int current_frame; //luu frame khi dang di chuyen ma dung lai
#pragma endregion
	animationSet->at(0)->Render(1, x, y, alpha);
	RenderBoundingBox();
}


void AnimationIntro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

