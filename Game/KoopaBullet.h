#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"

#define KOOPABULLET_WALKING_SPEED 0.04f;

#define KOOPABULLET_BBOX_WIDTH 16
#define KOOPABULLET_BBOX_HEIGHT 24
#define KOOPABULLET_BBOX_HEIGHT_DIE 9

#define KOOPABULLET_STATE_WALKING	0
//#define KOOPABULLET_STATE_DIE		1


class KoopaBullet : public Entity
{
public:
	bool hasWing = true;
	bool isGrounded;
	DWORD sulkyMario;  //doi mario bo ko them duoi nua
	Player* Mario;
	DWORD readyToFlyHigh;
	int countFly;
	bool isDeath;
	bool isDoneDeath;
	int ani;
	vector <LPGAMEENTITY> listEffect;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	void SetSpeed();
	KoopaBullet(float width, float height);
	void SetDirection();
	DWORD timeRenderAniDie;
	KoopaBullet(Player* mario);
	virtual void SetState(int state);
};

