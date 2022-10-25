#pragma once
#include "GameObj.h"
#include "Player.h"
#include "Block.h"
#include "Buff.h"
class Ball: public GameObj {
public:
	int speed_x, speed_y;
	bool caught;
	Ball(int x, int y, const char* path, int c1, int c2);
	void BallMotion();
	void BallDefCollision(GameObj* map);
	void BallWallCollision(GameObj* map);
	void BallPlayerCollision(Player* p);
	void BallBlockCollision(Block* b,Buff* buff,Buff* debuff);
};