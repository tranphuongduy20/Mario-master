#pragma once
#include "Entity.h"

#define ENDSCENE_BBOX_WIDTH  16
#define ENDSCENE_BBOX_HEIGHT 16

#define	ENDSCENE_STATE_COLLISION 10

class EndScene : public Entity
{
public:
	float frameW, frameH;
	float oldY;
	bool isColliCbrick;
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	EndScene(float posX, float posY, float frameW, float frameH);
};


