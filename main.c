#include <stdlib.h>
#include <time.h>

#include "depen/asteroid.h"
#include "depen/constants.h"
#include "depen/game_asteroids.h"
#include "depen/game_bullets.h"
#include "depen/game_player.h"
#include "depen/game_score.h"
#include "depen/game_ui.h"
#include "depen/player.h"
#include "raylib.h"
#include "raymath.h"

static Texture2D _spriteSheet;

void updateDrawFrame(void);

int main(void) {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  InitPlayer();

  _spriteSheet = LoadTexture("./assets/spritesheet.png");

  while (!WindowShouldClose()) {
    updateDrawFrame();
  }

  UnloadTexture(_spriteSheet);
  CloseWindow();
  return 0;
}

void updateDrawFrame(void) {
  UpdateAsteroids();
  UpdateBullets();
  UpdatePlayer();

  BeginDrawing();
  ClearBackground(BLACK);

  DrawAsteroids(_spriteSheet);
  DrawBullets(_spriteSheet);
  DrawPlayer(_spriteSheet);
  DrawHealthBar();
  DrawScore();

  EndDrawing();
}
