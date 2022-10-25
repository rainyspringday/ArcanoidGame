#pragma once
#include "Framework.h"
class GameObj {
private:
	int width, height;
	Sprite* sprite;
public:
	int pos_x, pos_y;
	GameObj( int x, int y,const char* path);
	void DrawObj(int a[], GameObj* map);
	int GetWidth();
	int GetHeight();
	bool LossCondition(GameObj* map);
	~GameObj();
};