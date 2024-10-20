#include "snake.h"

Snake::Snake(int _posX, int _posY, int _size)
{
  initPosX = _posX;
  initPosY = _posY;
  posX = initPosX;
  posY = initPosY;
  posDx = 0;
  posDy = 0;
  length = 1;
  size = _size;
  speed = _size;
  direction = UP;
  bodys[0] = {posX, posY};
  return;
}

bool Snake::checkHitWall()
{
  if (posX < 0) return true;
  if (posX > WINDOW_WIDTH - size) return true;
  if (posY < 0) return true;
  if (posY > WINDOW_HEIGHT - size) return true;
  return false;
}

void Snake::moveUp()
{
  if (direction == (-UP)) return;
  posDx = 0;
  posDy = -speed;
  direction = UP;
  return;
}

void Snake::moveDown()
{
  if (direction == (-DOWN)) return;
  posDx = 0;
  posDy = speed;
  direction = DOWN;
  return;
}

void Snake::moveRight()
{
  if (direction == (-RIGHT)) return;
  posDx = speed;
  posDy = 0;
  direction = RIGHT;
  return;
}

void Snake::moveLeft()
{
  if (direction == (-LEFT)) return;
  posDx = -speed;
  posDy = 0;
  direction = LEFT;
  return;
}

bool Snake::moveUpdate()
{
  if (!checkHitWall())
  {
    posX += posDx;
    posY += posDy;
    for (int i = length - 1; i > 0; i--)
    {
      bodys[i] = bodys[i - 1];
    }
    bodys[0].posX = posX;
    bodys[0].posY = posY;
  } else {
    return true;
  }
  for (int i = 0; i < length; i++)
  {
    DrawBox(bodys[i].posX, bodys[i].posY, bodys[i].posX + size, bodys[i].posY + size, GetColor(255, 0, 0), TRUE);
  }
  DrawBox(posX, posY, posX + size, posY + size, GetColor(238, 120, 0), TRUE);

  return false;
}

void Snake::lengthen()
{
  if (length >= MAX_SNAKE_LENGTH) return;
  length++;
  return;
}

bool Snake::isHitBody()
{
  for (int i = 1; i < length - 1 + 1; i++)
  {
    if (posX == bodys[i].posX && posY == bodys[i].posY) return true;
  }
  return false;
}

int Snake::getPosX() { return posX; }
int Snake::getPosY() { return posY; }

void Snake::init()
{
  posX = initPosX;
  posY = initPosY;
  posDx = 0;
  posDy = 0;
  length = 1;
  return;
}
