#pragma once
#include "Block.h"
#include "Player.h"
class Buff :public Block
{
public:
	bool is_active;
	unsigned int lifestart;
	Buff(int x, int y, const char* path,int a);
	void BuffMapCollision(GameObj* map);
	void BuffPlayerCollision(Player* p);
	bool BuffBlockCollision(Block* b);
	void BuffTimer(unsigned int a);
};