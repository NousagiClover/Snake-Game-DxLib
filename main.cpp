#include "DxLib.h"
#include "game.h"
#include "fps.h"
#include "snake.h"
#include "food.h"
#include "score.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
  SetOutApplicationLogValidFlag(LOG_FILE); // Log.txtファイルを生成するか
  ChangeWindowMode(WINDOW_MODE); // ウィンドウモードにするか
  SetMainWindowText(WINDOW_TITLE); // ウィンドウのタイトル
  SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32); // ウィンドウの解像度
  SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // ウィンドウのサイズ
  SetWaitVSyncFlag(WINDOW_VSYNC); // リフレッシュレートをモニターと同期するか
  SetAlwaysRunFlag(WINDOW_INACTIVE_RUN); // ウィンドウが非アクティブでも処理を続行するか
  SetBackgroundColor(WINDOW_BG_COLOR_RED, WINDOW_BG_COLOR_GREEN, WINDOW_BG_COLOR_BLUE, WINDOW_BG_COLOR_ALPHA); // ウィンドウの背景色
  SetWindowIconID(APP_ICON);

  if (DxLib_Init() == -1)
  {
    return -1;
  }

  fpsInit();
  SetDrawScreen(DX_SCREEN_BACK);

  Snake snake = Snake(100, 100, SNAKE_SIZE);
  Food food = Food(SNAKE_SIZE);

  Score score = Score(35);
  GameScene gameScene = TITLE;
  bool gameLoop = TRUE;
  
  // 効果音
  int sound_start = LoadSoundMem(SOUND_START);
  int sound_get_food = LoadSoundMem(SOUND_GET_FOOD);
  int sound_gameover = LoadSoundMem(SOUND_GAMEOVER);

  while (gameLoop)
  {
    if (ProcessMessage() != 0) break;
    if (ClearDrawScreen() != 0) break;

    fpsCheck();

    if (!score.check())
    {
      gameScene = CHEATING;
      gameLoop = FALSE;
      continue;
    }

    switch (gameScene)
    {
    case TITLE:
      LoadGraphScreen(0, 0, GAME_TITLE_IMG, FALSE);
      ScreenFlip();
      while (TRUE)
      {
        if (ProcessMessage() != 0)
        {
          gameLoop = FALSE;
          break;
        }
        if (CheckHitKey(KEY_INPUT_RETURN)) break;
      }
      gameScene = PLAY;
      PlaySoundMem(sound_start, DX_PLAYTYPE_BACK);
      break;
    case PLAY:
      SetFontSize(20);
      if (CheckHitKey(KEY_INPUT_W))
        snake.moveUp();
      if (CheckHitKey(KEY_INPUT_S))
        snake.moveDown();
      if (CheckHitKey(KEY_INPUT_D))
        snake.moveRight();
      if (CheckHitKey(KEY_INPUT_A))
        snake.moveLeft();

      food.place();
      if (food.isHit(snake.getPosX(), snake.getPosY()))
      {
        food.reset();
        snake.lengthen();
        score.addScore(1);
        score.hiScoreUpdate();
        PlaySoundMem(sound_get_food, DX_PLAYTYPE_BACK);
      }

      if (snake.moveUpdate()) gameScene = GAMEOVER;
      if (snake.isHitBody()) gameScene = GAMEOVER;

      drawFps(10, 0);
      DrawFormatString(10, 20, GetColor(0, 0, 0), "Score: %d", score.getScore());
      DrawFormatString(10, 40, GetColor(0, 0, 0), "Hi Score: %d", score.getHiScore());
      fpsWait();
      ScreenFlip();
      break;
    case GAMEOVER:
      ClearDrawScreen();
      SetFontSize(GAMEOVER_TEXT_SIZE);

      // ゲームオーバータイトル
      DRAW_CENTER_TEXT(GAMEOVER_TITLE, WINDOW_HEIGHT / 4 - GAMEOVER_TEXT_SIZE, 0, GetColor(0, 0, 0));
      // スコア
      DrawFormatString(GET_STRING_CENTER(GetDrawFormatStringWidth(GAMEOVER_RESULT_SCORE, score.getScore())),
        WINDOW_HEIGHT / 4, GetColor(0, 0, 0), GAMEOVER_RESULT_SCORE, score.getScore());
      // ハイスコア
      DrawFormatString(GET_STRING_CENTER(GetDrawFormatStringWidth(GAMEOVER_RESULT_HISCORE, score.getHiScore())),
        WINDOW_HEIGHT / 4 + GAMEOVER_TEXT_SIZE, GetColor(0, 0, 0), GAMEOVER_RESULT_HISCORE, score.getHiScore());

      // ヒント
      DRAW_CENTER_TEXT(GAMEOVER_HINT_1, WINDOW_HEIGHT / 2, 0, GetColor(0, 0, 0));
      DRAW_CENTER_TEXT(GAMEOVER_HINT_2, WINDOW_HEIGHT / 2 + GAMEOVER_TEXT_SIZE, 0, GetColor(0, 0, 0));
      ScreenFlip();
      PlaySoundMem(sound_gameover, DX_PLAYTYPE_BACK);
      while (TRUE)
      {
        if (ProcessMessage() != 0)
        {
          gameLoop = FALSE;
          break;
        }
        if (CheckHitKey(KEY_INPUT_RETURN))
        {
          // 初期化処理
          gameLoop = TRUE;
          gameScene = PLAY;
          snake.init();
          food.reset();
          score.zeroScore();
          PlaySoundMem(sound_start, DX_PLAYTYPE_BACK);
          break;
        } else if (CheckHitKey(KEY_INPUT_SPACE)) {
          gameLoop = FALSE;
          break;
        }
      }
      break;
    default:
      MessageBox(NULL, "予期せぬゲームシーンのため、ゲームを終了します", "予期せぬエラー", MB_OK);
      gameLoop = FALSE;
      break;
    }
  }

  if (gameScene == CHEATING)
  {
    MessageBox(NULL, "あなたは不正行為をしたのでゲームを終了します", "チート検知", MB_OK);
  }

  DxLib_End();

  return 0;
}
