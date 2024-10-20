#pragma once

#include "DxLib.h"
#include "game.h"
#include "snake.h"

class Food
{
private:
	int posX;
	int posY;
	int size;
	int hFood;
public:
	Food(int _size);
	void place();
	bool isHit(int _snakePosX, int _snakePosY);
	void reset();
};
