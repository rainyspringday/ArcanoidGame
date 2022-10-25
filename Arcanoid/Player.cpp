#include "Player.h"
Player::Player(int x, int y, const char* path):GameObj(x,y,path)
{
	dir = 0;
}
bool Player::LossCondition(Block* block)//collision with blocks
{
	bool t = false;
	if (pos_x<block->pos_x + block->GetWidth() && pos_x + GetWidth()>block->pos_x&&block->is_destroyed==false)
	{
		if (pos_y == block->pos_y+block->GetHeight())
		{
			t = true;
		}
	}
	return t;
}
void Player::PlayerMotion(GameObj* map)
{
	if(pos_x + 1 * dir!=-1&& pos_x + 1 * dir!= map->GetWidth()- this->GetWidth() + 1)
	{
		pos_x = pos_x + 1 * dir;
	}
}