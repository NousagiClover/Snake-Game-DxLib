#include "food.h"

Food::Food(int _size)
{
  posX = GetRand(WINDOW_WIDTH / SNAKE_SIZE - 1) * SNAKE_SIZE;
  posY = GetRand(WINDOW_HEIGHT / SNAKE_SIZE - 1) * SNAKE_SIZE;
  size = _size;
  hFood = LoadGraph(GAME_FOOD_IMG);
  return;
}

void Food::place()
{
  // DrawBox(posX, posY, posX + size, posY + size, GetColor(0, 255, 255), TRUE);
  DrawGraph(posX, posY, hFood, TRUE);
  return;
}

bool Food::isHit(int _snakePosX, int _snakePosY)
{
  if (posX != _snakePosX) return false;
  if (posY != _snakePosY) return false;
  return true;
}

void Food::reset()
{
  posX = GetRand(WINDOW_WIDTH / SNAKE_SIZE - 1) * SNAKE_SIZE;
  posY = GetRand(WINDOW_HEIGHT / SNAKE_SIZE - 1) * SNAKE_SIZE;
  return;
}
