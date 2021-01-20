#pragma once
#include "Entity.h"
#include "Money.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define	CBRICK_STATE_COLLISION 10

class CBrickV2 : public Entity
{
public:
	vector<Money*> money;
	float frameW, frameH;
	float oldY;
	bool isColliCbrick;
	int count = 0;
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CBrickV2(float posX, float posY, float frameW, float frameH);
	~CBrickV2();
};

