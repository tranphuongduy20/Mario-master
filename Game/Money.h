#pragma once
#include "Entity.h"

#define MONEY_WALKING_SPEED 0.04f;

#define MONEY_BBOX_WIDTH		8
#define MONEY_BBOX_HEIGHT		16


#define MONEY_STATE_WALKING		100

#define MONEY_ANI_WALKING		0

class Money : public Entity
{
public:
	DWORD timeDelay;
	vector <LPGAMEENTITY> listEffect;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	int alpha;
	float oldY;
	bool isDone;
	bool isCollis;
	bool isEmpty;
	bool isOnTop = false;
	bool isStart = false;
	Money(float posX, float posY);
	virtual void SetState(int state);
};



