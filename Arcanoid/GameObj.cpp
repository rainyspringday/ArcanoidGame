#include "GameObj.h"
#include <iostream>
using namespace std;
GameObj::GameObj( int x, int y,const char* path)
{
	
	pos_x = x;
	pos_y = y;
	sprite = createSprite(path);
	getSpriteSize(sprite, width, height);
}
void GameObj::DrawObj(int a[],GameObj* map)
{
	drawSprite(sprite, pos_x + (a[0] - map->GetWidth())/2, pos_y + (a[1]-map->GetHeight())/2);
}
int GameObj::GetWidth()
{
	return width;
}
int GameObj::GetHeight()
{
	return height;
}

bool GameObj::LossCondition(GameObj* map)
{
	bool t = false;
		if (pos_y >= map->GetHeight() - this->GetHeight()  - 100)
		{
			t = true;
		}
		return t;
}
