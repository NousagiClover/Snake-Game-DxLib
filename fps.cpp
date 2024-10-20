#include "fps.h"

FPS fps;

void fpsInit()
{
  fps.firstTakeTime = GetNowHiPerformanceCount();
  fps.nowTakeTime = fps.firstTakeTime;
  fps.oldTakeTime = fps.firstTakeTime;
  fps.deltatime = 0.000001f;
  fps.frameCount = 1;
  fps.average = 0; .0f;

  return;
}

void fpsCheck()
{
  fps.nowTakeTime = GetNowHiPerformanceCount();
  fps.deltatime = (fps.nowTakeTime - fps.oldTakeTime) / MILL_SECOND;
  fps.oldTakeTime = fps.nowTakeTime;

  if (fps.frameCount == GAME_FPS)
  {
    float totalFrameTime = fps.nowTakeTime - fps.firstTakeTime;
    float calcAverage = totalFrameTime / GAME_FPS;
    fps.average = MICRO_SECOND / calcAverage;
    fps.firstTakeTime = GetNowHiPerformanceCount();
    fps.frameCount = 1;
  }
  else {
    fps.frameCount++;
  }

  return;
}

void drawFps(int posX, int posY)
{
  DrawFormatString(posX, posY, GetColor(0, 0, 0), "FPS: %3.1f", fps.average);
  return;
}

void fpsWait()
{
  int wait = 0;
  wait = MICRO_SECOND / GAME_FPS * fps.frameCount - (fps.nowTakeTime - fps.firstTakeTime);
  wait /= MILL_SECOND;
  if (wait > 0 && wait <= WAIT_TIME_MILL)
  {
    WaitTimer(wait);
  }

  return;
}
