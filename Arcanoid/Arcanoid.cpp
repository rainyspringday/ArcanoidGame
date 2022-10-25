#include "Framework.h"
#include "GameObj.h"
#include "Player.h"
#include <iostream>
#include "Ball.h"
#include <stdlib.h>
#include "Block.h"
#include "Buff.h"
#include <ctime>

using namespace std;
/* Test Framework realization */

#define n 30  //blocks

int window[2]={600,800};
int margin_x = 0, margin_y = 0;
int end_game;
bool temp = false;
float target_x, target_y;
bool GameStart = false;
void Start();
int WinOrLoss();
GameObj* map;
GameObj* redline;
GameObj* defline;
Player* player;
Ball* ball;
Block* block;
Block* blocks[n];
Buff* buff;
Buff* debuff;

class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = window[0];
		height = window[1];
		fullscreen = false;
	}

	virtual bool Init() {
		map = new GameObj(0, 0, "data/background.png");
		redline = new GameObj(0, 700, "data/redline.png");
		defline = new GameObj(0, 700, "data/defline.png");
		player = new Player( 240, 680, "data/player.png");
		ball= new Ball(295, 670, "data/ball.png",0,0);
		block = new Block(0, 0, "data/block.png",40);
		buff =new Buff(0, 0, "data/buff.png",5);
		debuff = new Buff(0, 0, "data/debuff.png", 5);
		for (int i = 0; i < n; i++)
		{
			blocks[i] = new Block(block->GetWidth() * (i % 5) + 100,block->GetHeight() * (i / 5), "data/block.png",40);
		}
		showCursor(true);
		srand(time(NULL));
		margin_x = (window[0] - map->GetWidth()) / 2;
		margin_y = (window[1] - map->GetHeight()) / 2;
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		//drawing
		map->DrawObj(window,map);
		redline->DrawObj(window, map);
		if (buff->is_active == true)
		{
			defline->DrawObj(window, map);
		}
		player->DrawObj(window, map);
		ball->DrawObj(window, map);
		for (int i = 0; i < n; i++)
		{
			if (blocks[i]->is_destroyed == false)
				blocks[i]->DrawObj(window, map);
		}
		if (buff->is_destroyed == false)
		{
			buff->DrawObj(window, map);
		}
		if (debuff->is_destroyed == false)
		{
			debuff->DrawObj(window, map);
		}
		//logic
		if (GameStart == true)
		{
			//collisions
			if (buff->is_active == true)
			{
				ball->BallDefCollision(map);
			}
			ball->BallWallCollision(map);
			ball->BallPlayerCollision(player);
			for (int i = 0; i < n; i++)
			{
				ball->BallBlockCollision(blocks[i], buff,debuff);
			}
			buff->BuffMapCollision(map);
			buff->BuffPlayerCollision(player);
			debuff->BuffMapCollision(map);
			debuff->BuffPlayerCollision(player);
			buff->BuffTimer(getTickCount());
			for (int i = 0; i < n; i++)
			{
				buff->BuffBlockCollision(blocks[i]);
			}
			for (int i = 0; i < n; i++)
			{
				debuff->BuffBlockCollision(blocks[i]);
			}
			//motion
			player->PlayerMotion(map);
			ball->BallMotion();
			for (int i = 0; i < n; i++)
			{
				blocks[i]->BlockMotion();
			}
			for (int i = 0; i < n; i++)
			{
				temp = false;
				if (buff->BuffBlockCollision(blocks[i]) == true)
				{
					temp = true;
					break;
				}
			}
			if (temp == false)
			{
				buff->BlockMotion();
			}
			for (int i = 0; i < n; i++)
			{
				temp = false;
				if (debuff->BuffBlockCollision(blocks[i]) == true)
				{
					temp = true;
					break;
				}
			}
			if (temp == false)
			{
				debuff->BlockMotion();
			}
			//game result
			end_game = WinOrLoss();
			if (end_game > 0)
			{
				Start();
			}
		}
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		if (GameStart==false)
		{
			target_x = x ;
			target_y = y ;
		}
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		//starting shot direction
		if (button == FRMouseButton::LEFT&&GameStart==false)
		{
			if (target_x > 0 + margin_x  && target_x < map->GetWidth() + margin_x && target_y>0 + margin_y && target_y < map->GetHeight() - 100 + margin_y)
			{
				GameStart = true;
				showCursor(false);
				float a = map->GetHeight() - 100 - target_y + margin_y;
				float b = map->GetWidth() / 2 - target_x + margin_x;
				float c = a / b;


				if (target_x < map->GetWidth()/2 + margin_x && abs(c) < 1)
				{
					ball->speed_x = 1;
					ball->speed_y = 1;
				}
				else if (target_x > map->GetWidth()/2 + margin_y && abs(c) < 1)
				{
					ball->speed_x = -1;
					ball->speed_y = 1;
				}
				else
				{
					ball->speed_x = 0;
					ball->speed_y = 1;
				}
			}
		}
	}

	virtual void onKeyPressed(FRKey k) {
		if (GameStart == true)
		{
			switch (k)
			{
			case FRKey::RIGHT:
				player->dir = 1;
				break;

			case FRKey::LEFT:
				player->dir = -1;
				break;
			}
		}
	}

	virtual void onKeyReleased(FRKey k) {
			switch (k)
			{
			case FRKey::RIGHT:
				player->dir = 0;
				break;

			case FRKey::LEFT:
				player->dir = 0;
				break;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}
};


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc-1; i++)
	{
		cout << window[i] << endl;
		window[i] = atoi(argv[i+1]);
	}
	return run(new MyFramework);
}

void Start()
{
	player->pos_x = 240;
	player->pos_y = 680;
	ball->pos_x = 295;
	ball->pos_y = 670;
	end_game = 0;
	GameStart = false;
	showCursor(true);
	for (int i = 0; i < n; i++)
	{
		blocks[i]->is_destroyed = false;
		blocks[i]->pos_x = blocks[i]->GetWidth() * (i % 5) + 100;
		blocks[i]->pos_y = blocks[i]->GetHeight() * (i / 5);
	}
	buff->is_destroyed = true;
	buff->is_active = false;
	debuff->is_destroyed = true;
	debuff->is_active = false;
}
int WinOrLoss()
{
	end_game = 0;
	int count = 0;
	if (buff->is_active == false)
	{
		if (ball->LossCondition(map) == true)
		{
			end_game++;
		}
	}
	if (debuff->is_active == true)
	{
		end_game++;
	}
	for (int i = 0; i < n; i++)
	{
		if (blocks[i]->LossCondition(map) == true)
		{
			end_game++;
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (player->LossCondition(blocks[i]) == true)
		{
			end_game++;
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (blocks[i]->is_destroyed == true)
		{
			count++;
		}

	}
	if (ball->caught == true && count == n)
	{
		end_game++;
	}
	return end_game;
}