#include "Block.h"

Block::Block(int x, int y, const char* path,int a):GameObj(x,y,path)
{
	rate = a;
	is_destroyed = false;
	tick = 0;
}

void Block::BlockMotion()
{
	tick++;
	if (rate != 0)
	{
		if (tick == rate)//40 - block 5 - buff
		{
			tick = 0;
			pos_y = pos_y + 1;
		}
	}
}

