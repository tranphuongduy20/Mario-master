#pragma once
#include "Entity.h"

#define BLINK_TIME 1000

#define VISIBLE_TIME	725
#define INVISIBLE_TIME	250

class SpeechBubble : public Entity
{
	bool isVisible = true;
	float visibleStartTime = 0;
	float invisibleStartTime = 0;
public:
	void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	void Render();
};

