#pragma once
#include "GameObj.h"
class Block :public GameObj {
private:
	int tick;
public:
	int rate;
	bool is_destroyed;
	Block(int x, int y, const char* path,int a);
	void BlockMotion();
};