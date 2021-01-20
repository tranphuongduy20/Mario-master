#include "BrickMove.h"

void BrickMove::Render()
{
	animationSet->at(0)->Render(nx, x, y);
	RenderBoundingBox();
}

void BrickMove::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

BrickMove::BrickMove(float posX, float posY, float frameW, float frameH, Player* player)
{
	this->player = player;
	x = posX;
	y = posY;
	oldY = posY;
	//isColliCbrick = false;
	tag = EntityType::MOVEBRICK;
	this->frameH = frameH;
	this->frameW = frameW;
	vx = -0.02;
	vy = 0;
}

void BrickMove::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case MOVEBRICK_STATE_COLLISION:
		if (!isCollid)
		{
			vy = 0;
			timeDelayed = 0;
			vx = 0;
			isCollid = true;
		}
		break;
	}
}

void BrickMove::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	if (isCollid)
		timeDelayed += dt;
	if (timeDelayed > 200)
		isFalling = true;
	if (isFalling)
		vy = 0.05;
	Entity::Update(dt, coObjects);
	x += dx;
	y += dy;
}