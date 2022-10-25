#include "Ball.h"
#include <iostream>
using namespace std;
Ball::Ball(int x, int y, const char* path, int c1, int c2) :GameObj(x,y, path)
{
	caught = false;
	speed_x = c1;
	speed_y = c2;
}
void Ball::BallMotion()
{
	pos_x = pos_x - speed_x;
	pos_y = pos_y - speed_y;
}
void Ball::BallWallCollision(GameObj* map)
{
	if (pos_y - speed_y < 0|| pos_y - speed_y > map->GetHeight())
	{
		speed_y = -speed_y;
	}
	if (pos_x - speed_x < 0 || pos_x - speed_x > map->GetWidth())
	{
		speed_x = -speed_x;
	}
}
void Ball::BallPlayerCollision(Player* p)
{
	if (pos_y - speed_y == p->pos_y - GetHeight()+1 && pos_x + 5 >= p->pos_x && pos_x < p->pos_x + 35)
	{
		speed_x = 1;
		speed_y = 1;
		caught = true;
	}
	else if (pos_y - speed_y == p->pos_y - GetHeight()+1 && pos_x >= p->pos_x + 35 && pos_x < p->pos_x + 85)
	{
		speed_x = 0;
		speed_y = 1;
		caught = true;
	}
	else if (pos_y - speed_y == p->pos_y - GetHeight()+1 && pos_x >= p->pos_x + 85 && pos_x < p->pos_x + 125)
	{
		speed_x = -1;
		speed_y = 1;
		caught = true;
	}
	else {
		caught = false;
	}
}

void Ball::BallBlockCollision(Block* b,Buff* buff,Buff* debuff)
{
	if (pos_x + GetWidth() > b->pos_x && pos_x < b->pos_x + b->GetWidth() && b->is_destroyed == false)
	{
		if (pos_y - speed_y + GetHeight() == b->pos_y || pos_y - speed_y == b->pos_y + b->GetHeight())
		{
			b->is_destroyed = true;
			speed_y = -speed_y;
			if (rand() % 100 > 80)
			{
				if (rand() % 2 == 0)
				{
					if (buff->is_destroyed == true && buff->is_active == false)
					{
						buff->is_destroyed = false;
						buff->pos_x = b->pos_x + b->GetWidth() / 2 - buff->GetWidth() / 2;
						buff->pos_y = b->pos_y;
					}
				}
				else {
					if (debuff->is_destroyed == true)
					{
						debuff->is_destroyed = false;
						debuff->pos_x = b->pos_x + b->GetWidth() / 2 - debuff->GetWidth() / 2;
						debuff->pos_y = b->pos_y;
					}
				}
			}
		}
	}
	else if (pos_y + GetHeight() > b->pos_y && pos_y<b->pos_y + b->GetHeight() && b->is_destroyed == false)
	{
		if (pos_x - speed_x + GetWidth() == b->pos_x || pos_x - speed_x == b->pos_x + b->GetWidth())
		{
			b->is_destroyed = true;
			speed_x = -speed_x;
			if (rand() % 100 + 1 > 80)
			{
				if (rand() % 2 == 0)
				{
					if (buff->is_destroyed == true && buff->is_active == false)
					{
						buff->is_destroyed = false;
						buff->pos_x = b->pos_x + b->GetWidth() / 2 - buff->GetWidth() / 2;
						buff->pos_y = b->pos_y;
					}
				}
				else {
					if (debuff->is_destroyed == true)
					{
						debuff->is_destroyed = false;
						debuff->pos_x = b->pos_x + b->GetWidth() / 2 - debuff->GetWidth() / 2;
						debuff->pos_y = b->pos_y;
					}
				}
			}
		}
	}
	else if (b->is_destroyed == false)
	{
		if (pos_y - speed_y + GetHeight() == b->pos_y || pos_y - speed_y == b->pos_y + b->GetHeight())
		{
			if (pos_x - speed_x + GetWidth() == b->pos_x || pos_x - speed_x == b->pos_x + b->GetWidth())
			{
				b->is_destroyed = true;
				speed_x = -speed_x;
				speed_y = -speed_y;
				if (rand() % 100 > 80)
				{
					if (rand() % 2 == 0)
					{
						if (buff->is_destroyed == true && buff->is_active == false)
						{
							buff->is_destroyed = false;
							buff->pos_x = b->pos_x + b->GetWidth() / 2 - buff->GetWidth() / 2;
							buff->pos_y = b->pos_y;
						}
					}
					else {
						if (debuff->is_destroyed == true)
						{
							debuff->is_destroyed = false;
							debuff->pos_x = b->pos_x + b->GetWidth() / 2 - debuff->GetWidth() / 2;
							debuff->pos_y = b->pos_y;
						}
					}
				}
			}
		}
	}
}
void Ball::BallDefCollision(GameObj* map)
{
	if (pos_y+GetHeight() > map->GetHeight() - 100)
	{
		speed_y = -speed_y;
	}
}

