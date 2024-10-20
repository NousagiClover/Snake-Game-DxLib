#pragma once

#define LOG_FILE FALSE
#define WINDOW_MODE TRUE
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500
#define WINDOW_TITLE "Snake Game"
#define WINDOW_BG_COLOR_RED 255
#define WINDOW_BG_COLOR_GREEN 255
#define WINDOW_BG_COLOR_BLUE 255
#define WINDOW_BG_COLOR_ALPHA 0
#define WINDOW_VSYNC TRUE
#define WINDOW_INACTIVE_RUN TRUE
#define APP_ICON 100
#define SNAKE_SIZE 50
#define GAMEOVER_TEXT_SIZE 30
#define GAMEOVER_TITLE "ゲームオーバー"
#define GAMEOVER_RESULT_SCORE "今回のスコア: %d"
#define GAMEOVER_RESULT_HISCORE "今回のハイスコア: %d"
#define GAMEOVER_HINT_1 "エンターでリトライ"
#define GAMEOVER_HINT_2 "スペースでゲーム終了"
#define GAME_TITLE_IMG "res/title.png"
#define GAME_FOOD_IMG "res/apple.png"
#define SOUND_GET_FOOD "res/get_food.mp3"
#define SOUND_START "res/start.mp3"
#define SOUND_GAMEOVER "res/game_over.mp3"

#define WAIT_KEY(key)\
while (TRUE){if (CheckHitKey(key)) break;}
#define GET_STRING_CENTER(stringWidth) (WINDOW_WIDTH / 2 - stringWidth / 2)
#define DRAW_CENTER_TEXT(text, height, widthOffset, color)\
DrawString(GET_STRING_CENTER(GetDrawStringWidth(text, sizeof(text))) + widthOffset, height, text, color)

enum GameScene
{
  TITLE,
  PLAY,
  GAMEOVER,
  CHEATING
};
