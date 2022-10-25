#include "Buff.h"
Buff::Buff(int x, int y, const char* path,int a):Block(x,y,path,a)
{
	is_destroyed = true;
	is_active = false;
	lifestart = 0;
}
void Buff::BuffMapCollision(GameObj *map)
{
	if (pos_y >= map->GetHeight() - this->GetHeight() - 100)
	{
		is_destroyed = true;
	}
}
void Buff::BuffPlayerCollision(Player* p)
{
	if (pos_y + GetHeight() == p->pos_y && pos_x + GetWidth() >= p->pos_x && pos_x - GetWidth()< p->pos_x + p->GetWidth())
	{
		is_destroyed = true;
		is_active = true;
		lifestart = getTickCount();
	}
}
bool Buff::BuffBlockCollision(Block* block)
{
	bool t = false;
	if (pos_x<block->pos_x + block->GetWidth() && pos_x + GetWidth()>block->pos_x && block->is_destroyed == false)
	{
		if (pos_y + GetHeight() == block->pos_y)
		{
			t = true;
		}
	}
	return t;
}
void Buff::BuffTimer(unsigned int a)
{
	if (a - lifestart > 10000)
	{
		is_active = false;
	}
}
