#pragma once
#pragma once

#include "Entity.h"

#define WM_MARIO_MOVE_SPEED		0.05f

#define WM_MARIO_ANI_SMALL		0
#define WM_MARIO_ANI_BIG		1
#define WM_MARIO_ANI_RACCOON	2
#define WM_MARIO_ANI_FIRE		3


class WorldMapMario : public Entity
{

public:
	bool isMoving = false;
	float startMovingXPos = 0;
	float startMovingYPos = 0;
	WorldMapMario();
	void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	void Render();
	void Move(D3DXVECTOR2 direction);
};



