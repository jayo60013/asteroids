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

static bool DrawButton(Rectangle r, char *text) {
  Vector2 mousePos = GetMousePosition();
  Color btnColor = RAYWHITE;
  if (CheckCollisionPointRec(mousePos, r)) {
    btnColor = Fade(RAYWHITE, .7f);
  }

  DrawRectangleRec(r, btnColor);
  const int fontSize = 30;
  float textLength = MeasureText(text, fontSize);
  int xPos = r.x + (r.width / 2) - (textLength / 2);
  int yPos = r.y + (r.height / 2) - (fontSize / 2);
  DrawText(text, xPos, yPos, fontSize, BLACK);
  if (CheckCollisionPointRec(mousePos, r) &&
      IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    return true;
  }
  return false;
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

    if (DrawButton(topBtn, "PLAY AGAIN")) {
      SetState(GAME_PLAYING);
      return;
    }

    if (DrawButton(bottomBtn, "QUIT")) {
      SetState(GAME_MAIN_MENU);
      return;
    }
    break;
  case GAME_MAIN_MENU:
    if (DrawButton(topBtn, "ASTEROIDS")) {
      SetState(GAME_PLAYING);
      return;
    }
    if (DrawButton(bottomBtn, "QUIT")) {
      _quitGame = true;
      return;
    }
    break;
  }
}

void GameOver(void) { SetState(GAME_OVER); }
