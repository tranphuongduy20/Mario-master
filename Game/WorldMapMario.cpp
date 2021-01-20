#include "WorldMapMario.h"
WorldMapMario::WorldMapMario()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(1));
	x = 200;
	y = 385;
}

void WorldMapMario::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);
	if (isMoving)
	{
		if (abs(x - startMovingXPos) >= 31 || abs(y - startMovingYPos) >= 31)
		{
			vx = 0;
			vy = 0;
			isMoving = false;
		}
	}

	x += dx;
	y += dy;
}

void WorldMapMario::Render()
{
	animationSet->at(0)->Render(nx, x, y);
}

void WorldMapMario::Move(D3DXVECTOR2 dir)
{
	if (isMoving)
		return;

	isMoving = true;
	startMovingXPos = x;
	startMovingYPos = y;

	if (dir.x == 1)
		vx = WM_MARIO_MOVE_SPEED;
	else if (dir.x == -1)
		vx = -WM_MARIO_MOVE_SPEED;

	if (dir.y == 1)
		vy = -WM_MARIO_MOVE_SPEED;
	else if (dir.y == -1)
		vy = WM_MARIO_MOVE_SPEED;

}
