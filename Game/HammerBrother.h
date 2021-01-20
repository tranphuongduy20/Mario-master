#pragma once
#include "Entity.h"

#define HAMMER_BROTHER_SPEED						0.015f
#define HAMMER_BROTHER_DISTANCE_WALK_BEFORE_TURN	8

class HammerBrother :public Entity
{
public:
	HammerBrother(float x, float y);

	void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	void Render();
};
