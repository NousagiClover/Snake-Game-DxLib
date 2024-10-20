#pragma once

#include "DxLib.h"
#include "game.h"

#define MAX_SNAKE_LENGTH 64

class Snake
{
private:
  enum Direction
  {
    UP = 1,
    DOWN = -1,
    RIGHT = 2,
    LEFT = -2
  };
  typedef struct _Body
  {
    int posX;
    int posY;
  } Body;

  bool checkHitWall();

  int initPosX;
  int initPosY;
  int posX;
  int posY;
  int posDx;
  int posDy;
  int length;
  int size;
  int speed;
  Direction direction;
  Body bodys[MAX_SNAKE_LENGTH];
public:
  Snake(int _posX, int _posY, int _size);
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  bool moveUpdate();
  void lengthen();
  bool isHitBody();
  int getPosX();
  int getPosY();
  void init();
};
