#pragma once
#include "Block.h"
#include "GameObj.h"

class Player :public GameObj {
public:
	int dir;
	Player(int x, int y, const char* path);
	bool LossCondition(Block* block);
	void PlayerMotion(GameObj* map);
};