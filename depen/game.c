#include "game.h"
#include <raylib.h>

static GameState _state;
static Texture2D _spriteSheet;

extern bool _quitGame;

static void SetState(GameState state) {
  switch (state) {
  case GAME_MAIN_MENU:
    break;
  case GAME_PLAYING:
    ResetAsteroids();
    InitPlayer();
    ResetBullets();
    ResetScore();
    break;
  case GAME_OVER:
    break;
  }
  _state = state;
}

void InitGame(void) {
  InitPlayer();
  _spriteSheet = LoadTexture("./assets/spritesheet.png");
}

void DestroyGame(void) { UnloadTexture(_spriteSheet); }

void UpdateGame(void) {
  UpdateAsteroids();
  UpdateBullets();
  UpdatePlayer();
}

void DrawGame(void) {
  const float btnWidth = 200;
  const float btnHeight = 80;
  const Rectangle topBtn = {(SCREEN_CENTER.x) - btnWidth / 2,
                            SCREEN_CENTER.y - btnHeight, btnWidth, btnHeight};
  const Rectangle bottomBtn = {(SCREEN_CENTER.x) - btnWidth / 2,
                               SCREEN_CENTER.y + btnHeight, btnWidth,
                               btnHeight};

  switch (_state) {
  case GAME_PLAYING:
    DrawAsteroids(_spriteSheet);
    DrawBullets(_spriteSheet);
    DrawPlayer(_spriteSheet);
    DrawScore();
    DrawHealthBar();
    break;
  case GAME_OVER:
    DrawAsteroids(_spriteSheet);

    DrawRectangleRec(SCREEN_AREA, Fade(BLACK, .5f));
    const int fontSize = 64;
    const char *gameover = "GAME OVER!";
    float measure = MeasureText(gameover, fontSize);
    DrawText(gameover, SCREEN_CENTER.x - measure / 2, fontSize * 1.5f, fontSize,
             WHITE);

    DrawScore();

    DrawRectangleRec(topBtn, RED);
    DrawText("PLAY AGAIN", topBtn.x, topBtn.y, 30, WHITE);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), topBtn)) {
      SetState(GAME_PLAYING);
      return;
    }

    DrawRectangleRec(bottomBtn, GREEN);
    DrawText("QUIT", bottomBtn.x, bottomBtn.y, 30, WHITE);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), bottomBtn)) {
      SetState(GAME_MAIN_MENU);
      return;
    }
    break;
  case GAME_MAIN_MENU:
    DrawRectangleRec(topBtn, RED);
    DrawText("ASTEROIDS", topBtn.x, topBtn.y, 30, WHITE);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), topBtn)) {
      SetState(GAME_PLAYING);
      return;
    }
    DrawRectangleRec(bottomBtn, GREEN);
    DrawText("QUIT", bottomBtn.x, bottomBtn.y, 30, WHITE);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), bottomBtn)) {
      _quitGame = true;
      return;
    }
    break;
  }
}

void GameOver(void) { SetState(GAME_OVER); }
