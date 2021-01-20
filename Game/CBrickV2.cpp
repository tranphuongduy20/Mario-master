#include "CBrickV2.h"
#include "Point.h"

void CBrickV2::Render()
{
	if (isColliCbrick)
	{
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(4));
		animationSet->at(1)->Render(nx, x, y);
	}
	else
	{
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(20));
		animationSet->at(0)->Render(nx, x, y);
	}

	for (int i = 0; i < money.size(); i++)
	{
		money.at(i)->Render();
	}
	//RenderBoundingBox();
}

void CBrickV2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

CBrickV2::CBrickV2(float posX, float posY, float frameW, float frameH)
{
	x = posX;
	y = posY;
	oldY = posY;
	isColliCbrick = false;
	tag = EntityType::CBRICKV2;
	this->frameH = frameH;
	this->frameW = frameW;
}

void CBrickV2::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case CBRICK_STATE_COLLISION:
		if (!isColliCbrick)
		{
			y -= 16;
			vy += 0.05;
			count++;
			Money* money1 = new Money(x+5, y);
			money.push_back(money1);
			money1->SetState(MONEY_STATE_WALKING);
			money1->make100 = true;
			money1->isEmpty = true;
			Game::GetInstance()->Score += 100;
			if (count >5)
				isColliCbrick = true;
		}
		break;
	}
}

void CBrickV2::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt, coObjects);

	for (int i = 0; i < money.size(); i++)
	{
		money.at(i)->Update(dt, coObjects);
	}
	x += dx;
	y += dy;
	if (y >= oldY)
	{
		y = oldY;
		vy = 0;
	}
	
}

