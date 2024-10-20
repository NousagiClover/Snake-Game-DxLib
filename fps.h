#pragma once

#include "DxLib.h"

#define GAME_FPS 10
#define MICRO_SECOND 1000000.f
#define MILL_SECOND 1000.f
#define WAIT_TIME_MILL 3000

typedef struct _FPS
{
  LONGLONG firstTakeTime = 0;
  LONGLONG nowTakeTime = 0;
  LONGLONG oldTakeTime = 0;
  float deltatime = 0.000001f;
  int frameCount = 1;
  float average = 0.0f;
} FPS;

extern FPS fps;

extern void fpsInit();
extern void fpsCheck();
extern void drawFps(int posX, int posY);
extern void fpsWait();
