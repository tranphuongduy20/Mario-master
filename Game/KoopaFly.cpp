#include "KoopaFly.h"
#include "Koopa.h"
#include "Point.h"
#include "BrokenBrick.h"
#include "Brick.h"
#include "CBrick.h"
#include "Goomba.h"
#include "Leaf.h"

KoopaFly::KoopaFly(Player* mario)
{
	tag = EntityType::KOOPAFLY;
	Mario = mario;
	
	SetState(KOOPA_GREEN_STATE_HAS_WING_FLY_LEFT);
	timeToFly = GetTickCount64();

}

void KoopaFly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDeath)
		return;
	left = x + 1;
	top = y + 11;
	bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	right = x + KOOPAS_BBOX_WIDTH;
	

	if (state == KOOPA_GREEN_STATE_REVIVE || state == KOOPA_GREEN_STATE_REVIVE_UP)
	{
		left = x;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else if (state == KOOPA_GREEN_STATE_WALKING_RIGHT || state == KOOPA_GREEN_STATE_WALKING_LEFT || state == KOOPA_GREEN_STATE_HAS_WING_FLY_LEFT || state == KOOPA_GREEN_STATE_HAS_WING_FLY_RIGHT)
	{
		top = y;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (state == KOOPA_GREEN_STATE_DIE_UP)
	{
		if (hitByWeapon)
			left = top = right = bottom = 0;
	}

}

void KoopaFly::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	if (isDeath)
		return;
	if (
		GetState() == KOOPA_GREEN_STATE_HOLDING ||
		GetState() == KOOPA_GREEN_STATE_HOLDING_UP)
	{
		if (Mario->level == MARIO_LEVEL_RACCOON)
		{
			if (Mario->nx > 0)
				SetPosition(Mario->x + 10, Mario->y - 5);
			else
				SetPosition(Mario->x - 14, Mario->y - 5);
		}
		else if (Mario->level == MARIO_LEVEL_SMALL)
		{
			if (Mario->nx > 0)
				SetPosition(Mario->x + 10, Mario->y - 15);
			else
				SetPosition(Mario->x - 13, Mario->y - 15);
		}
		else
		{
			if (Mario->nx > 0)
				SetPosition(Mario->x + 11, Mario->y - 5);
			else
				SetPosition(Mario->x - 13, Mario->y - 5);
		}
		//state = KOOPAS_ANI_DIE;
	}

	if (hasWing)
	{
		if (GetTickCount64() - timeToFly > 900 && !hitByWeapon)
		{
			SetState(KOOPA_GREEN_STATE_HAS_WING_FLY_LEFT);
			timeToFly = GetTickCount64();
		}
	}
	else
	{
		if (!Mario->holdthing && (last_state == KOOPA_GREEN_STATE_HOLDING || last_state == KOOPA_GREEN_STATE_HOLDING_UP))//de khi tha mai rua ra thi mai rua bi da
		{
			nx = Mario->nx;
			if (last_state == KOOPA_GREEN_STATE_HOLDING)
				SetState(KOOPA_GREEN_STATE_DIE_AND_MOVE);
			else if (last_state == KOOPA_GREEN_STATE_HOLDING_UP)
				SetState(KOOPA_GREEN_STATE_DIE_AND_MOVE_UP);
			hitByTail = false;
		}
		if (GetTickCount64() - timeToRevive > 8000 && (last_state == KOOPA_GREEN_STATE_DIE || last_state == KOOPA_GREEN_STATE_DIE_UP || last_state == KOOPA_GREEN_STATE_HOLDING || last_state == KOOPA_GREEN_STATE_HOLDING_UP))//koopas vao trang thai chuan bi hoi sinh
		{
			Mario->holdthing = false;
			if (last_state == KOOPA_GREEN_STATE_DIE || last_state == KOOPA_GREEN_STATE_HOLDING)
				SetState(KOOPA_GREEN_STATE_REVIVE);
			else if (last_state == KOOPA_GREEN_STATE_DIE_UP || last_state == KOOPA_GREEN_STATE_HOLDING_UP)
				SetState(KOOPA_GREEN_STATE_REVIVE_UP);
		}
		if (GetTickCount64() - timeToRevive > 10000 && (last_state == KOOPA_GREEN_STATE_REVIVE || last_state == KOOPA_GREEN_STATE_REVIVE_UP))
		{
			SetState(KOOPA_GREEN_STATE_WALKING_RIGHT);
			timeToRevive = 0;
		}
	}
	

	Entity::Update(dt);
	if (state != KOOPA_GREEN_STATE_HOLDING &&
		state != KOOPA_GREEN_STATE_HOLDING_UP)
		vy += 0.0005f * dt;
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

		x += min_tx * dx + nx * 0.5f;
		y += min_ty * dy + ny * 0.1f;

		if (ny != 0)
			vy = 0;
		if (ny != 0 && (state == KOOPA_GREEN_STATE_REVIVE_UP || state == KOOPA_GREEN_STATE_DIE_UP))
		{
			vx = 0;
		}

		//Collision logic with other objects

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//if (dynamic_cast<Brick*>(e->obj))
			//{
			//	if (e->nx != 0)
			//	{
			//		x += dx;
			//	}
			//}
			//else if (dynamic_cast<BrokenBrick*>(e->obj))
			//{
			//	if (GetState() == KOOPA_GREEN_STATE_DIE_AND_MOVE || GetState() == KOOPA_GREEN_STATE_DIE_AND_MOVE_UP)
			//	{
			//		BrokenBrick* brokenbrick = dynamic_cast<BrokenBrick*>(e->obj);
			//		//brokenbrick->isDestroyed = true;
			//		brokenbrick->SetState(STATE_DESTROYED);
			//		vx = -vx;
			//	}
			//}
			//else
			//{
			//	if (!hasWing)
			//	{
			//		if (e->nx != 0)
			//		{
			//			vx = -vx;
			//			if (GetState() != KOOPA_GREEN_STATE_DIE_AND_MOVE && GetState() != KOOPA_GREEN_STATE_DIE_AND_MOVE_UP && GetState() != KOOPA_GREEN_STATE_DIE_UP)
			//			{
			//				if (vx > 0)
			//					SetState(KOOPA_GREEN_STATE_WALKING_RIGHT);
			//				else
			//					SetState(KOOPA_GREEN_STATE_WALKING_LEFT);
			//			}
			//		}
			//	}
			//}
			
		}

	}
	for (int i = 0; i < listEffect.size(); i++)
	{
		listEffect[i]->Update(dt, coObjects);
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CheckCollisionWithBrick(coObjects);
}

void KoopaFly::CheckCollisionWithBrick(vector<LPGAMEENTITY>* coObjects)
{
	float l_brick, t_brick, r_brick, b_brick, l_koopa, t_koopa, r_koopa, b_koopa;
	GetBoundingBox(l_koopa, t_koopa, r_koopa, b_koopa);
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEENTITY e = coObjects->at(i);
		if (dynamic_cast<CBrick*>(e) && GetState() == KOOPA_GREEN_STATE_DIE_AND_MOVE)
		{
			CBrick* brick = dynamic_cast<CBrick*>(e);
			brick->GetBoundingBox(l_brick, t_brick, r_brick, b_brick);
			if (Entity::CheckAABB(l_brick, t_brick, r_brick, b_brick, l_koopa, t_koopa, r_koopa, b_koopa))
			{
				SetState(KOOPA_GREEN_STATE_DIE_UP);
				hitByWeapon = true;
			}
		}
	}
}

void KoopaFly::Render()
{
	if (isDoneDeath)
		return;
	if (isDeath)
	{
		animationSet->at(KOOPA_GREEN_STATE_DIE)->Render(nx, x, y);
		if (animationSet->at(ani)->GetCurrentFrame() == 4 && ani == KOOPA_GREEN_STATE_DIE)
		{
			isDoneDeath = true;
		}
		return;
	}
	//DebugOut(L"nx %d ani %d \n", this->nx, state);
	animationSet->at(state)->Render(-this->nx, x, y);
	for (int i = 0; i < listEffect.size(); i++)
	{
		listEffect[i]->Render();
	}
	//DebugOut(L"gia tri state %d \n", state);
	RenderBoundingBox();
}

void KoopaFly::SetState(int State)
{
	Entity::SetState(State);   // last_state de xac dinh trang thai truoc do cua koopas roi thuc hien cac truong hop
	switch (State)
	{
	case KOOPA_GREEN_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		last_state = KOOPA_GREEN_STATE_WALKING_RIGHT;
		break;
	case KOOPA_GREEN_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		last_state = KOOPA_GREEN_STATE_WALKING_LEFT;
		break;
	case KOOPA_GREEN_STATE_DIE:
		vx = 0;
		vy = 0;
		timeToRevive = GetTickCount64();
		last_state = KOOPA_GREEN_STATE_DIE;
		break;
	case KOOPA_GREEN_STATE_DIE_AND_MOVE:
		last_state = KOOPA_GREEN_STATE_DIE_AND_MOVE;
		vx = Mario->nx * 0.2;
		break;
	case KOOPA_GREEN_STATE_DIE_UP:
		if (Mario->nx > 0)
			vx = 0.05;
		else
			vx = -0.05;
		if (last_state != KOOPA_GREEN_STATE_DIE_AND_MOVE_UP)
			vy = -0.13;
		timeToRevive = GetTickCount64();
		last_state = KOOPA_GREEN_STATE_DIE_UP;
		break;
	case KOOPA_GREEN_STATE_DIE_AND_MOVE_UP:
		last_state = KOOPA_GREEN_STATE_DIE_AND_MOVE_UP;
		vx = Mario->nx * 0.2;
		break;
	case KOOPA_GREEN_STATE_REVIVE:
		last_state = KOOPA_GREEN_STATE_REVIVE;
		break;
	case KOOPA_GREEN_STATE_REVIVE_UP:
		last_state = KOOPA_GREEN_STATE_REVIVE_UP;
		break;
	case KOOPA_GREEN_STATE_HAS_WING_FLY_RIGHT:
		/*vx = KOOPAS_WALKING_SPEED + 0.01;
		vy = -0.18;*/
		break;
	case KOOPA_GREEN_STATE_HAS_WING_FLY_LEFT:
		/*vx = -KOOPAS_WALKING_SPEED + 0.01;
		vy = -0.18;*/
		break;
	case KOOPA_GREEN_STATE_HOLDING:
		last_state = KOOPA_GREEN_STATE_HOLDING;
		break;
	case KOOPA_GREEN_STATE_HOLDING_UP:
		last_state = KOOPA_GREEN_STATE_HOLDING_UP;
		break;
	}

}