#include "EndScene.h"
void EndScene::Render()
{
	animationSet->at(0)->Render(nx, x, y);
	//RenderBoundingBox();
}

void EndScene::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

EndScene::EndScene(float posX, float posY, float frameW, float frameH)
{
	x = posX;
	y = posY;
	oldY = posY;
	isColliCbrick = false;
	tag = EntityType::ENDSCENE;
	this->frameH = frameH;
	this->frameW = frameW;
}

void EndScene::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case ENDSCENE_STATE_COLLISION:
		if (!isColliCbrick)
		{
			//y -= 16;
			vy = -.2f;
			isColliCbrick = true;
		}
		break;
	}
}

void EndScene::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (y >= oldY)
	{
		y = oldY;
		vy = 0;
	}
}
