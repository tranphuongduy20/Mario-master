#pragma once
#include "Entity.h"
#define SHORT_PIPE_ANI						0
#define MEDIUM_PIPE_ANI						1
#define LONG_PIPE_ANI						2
#define HIDDEN_PIPE_ANI						3
#define MEDIUM_PIPE_PAIR_WITH_LONG_ONE_ANI	4

#define PIPE_WIDTH			32
#define SHORT_PIPE_HEIGHT	32
#define MEDIUM_PIPE_HEIGHT	48
#define LONG_PIPE_HEIGHT	208
class Pipe : public Entity
{
public:
	int pipeType;

	Pipe(int pipeType);
	virtual void Render();
	//virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

