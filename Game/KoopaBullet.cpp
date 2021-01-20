#include "KoopaBullet.h"
#include "Brick.h"
#include "CBrick.h"
#include "BrickStand.h"
#include "Point.h"

KoopaBullet::KoopaBullet(Player* mario)
{
	tag = EntityType::KOOPABULLET;

	SetState(KOOPABULLET_STATE_WALKING);
	
	Mario = mario;
	if (Mario->x - x > 0)
		nx = -1;
	else
		nx = 1;
}

void KoopaBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	bottom = top + KOOPABULLET_BBOX_HEIGHT;
	right = left + KOOPABULLET_BBOX_WIDTH;
	
}

void KoopaBullet::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	SetState(KOOPABULLET_STATE_WALKING);
	


	Entity::Update(dt);
	//if (GetState() != GOOMBA_STATE_DIE && GetState() != GOOMBA_RED_STATE_NO_WING_DIE)
	//	vy += 0.0005 * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!


		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;

		if (ny < 0)
			isGrounded = true;

		if (ny != 0)
			vy = 0;
		//Collision logic with other objects

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];
			

			
				if (dynamic_cast<CBrick*>(e->obj))
				{
					if (e->nx != 0)
						x += dx;
				}
				if (dynamic_cast<Brick*>(e->obj))
				{
					Brick* brick = dynamic_cast<Brick*>(e->obj);
					if (e->nx != 0)
					{
						x += dx;
					}
					else if (e->ny < 0)
					{
						if (x <= brick->x)
						{
							x = brick->x;
							this->nx = -this->nx;
							SetState(KOOPABULLET_STATE_WALKING);

						}
					}
				
				
			}
		}
	}
	for (int i = 0; i < listEffect.size(); i++)
	{
		listEffect[i]->Update(dt, coObjects);
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void KoopaBullet::Render()
{
	animationSet->at(state)->Render(nx, x, y);
	for (int i = 0; i < listEffect.size(); i++)
	{
		listEffect[i]->Render();
	}
	RenderBoundingBox();
}

void KoopaBullet::SetSpeed()
{
	if (nx > 0)
		vx = KOOPABULLET_WALKING_SPEED;
	if (nx < 0)
		vx = -KOOPABULLET_WALKING_SPEED;
}

void KoopaBullet::SetDirection()
{
	if (Mario->x - x > 0)
		nx = 1;
	else
		nx = -1;
}

void KoopaBullet::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case KOOPABULLET_STATE_WALKING:
		SetSpeed();
		break;
	}
}
