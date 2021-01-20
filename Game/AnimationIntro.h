#pragma once
#include "Entity.h"

class AnimationIntro : public Entity
{
	static AnimationIntro* instance;
public:
	int typeScene;
	AnimationIntro(float x = 40, float y = 60);
	static AnimationIntro* GetInstance();

	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects = NULL);
	virtual void Render();


	void SetType(int type) { typeScene = type; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

