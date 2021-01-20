#include <algorithm>
#include "debug.h"
#include "IntroScene.h"
#include "Game.h"


IntroScene::IntroScene(float x, float y) : Entity()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(2));
	this->x = x;
	this->y = y;
}
IntroScene* IntroScene::instance = NULL;
IntroScene* IntroScene::GetInstance()
{
	if (instance == NULL)
		instance = new IntroScene();
	return instance;
}

void IntroScene::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
#pragma endregion
}


void IntroScene::Render()
{
#pragma region Khai báo biến
	int ani = -1;
	int alpha = 255;
	int current_frame; //luu frame khi dang di chuyen ma dung lai
#pragma endregion
	animationSet->at(0)->Render(1, x, y, alpha);
	RenderBoundingBox();
}


void IntroScene::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

