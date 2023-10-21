#include <stdlib.h>
#include <time.h>

#include "depen/asteroid.h"
#include "depen/constants.h"
#include "depen/game_asteroids.h"
#include "depen/game_bullets.h"
#include "depen/game_score.h"
#include "depen/player.h"
#include "raylib.h"
#include "raymath.h"

static Player _player;
static Texture2D _spriteSheet;

void updateDrawFrame(void);

int main(void) {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  _player = (Player){.pos = SCREEN_CENTER,
                     .vel = {0.f, 0.f},
                     .acc = {0.f, 0.f},
                     .rot = 180.f,
                     .lastFire = -1.f};

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
  PlayerUpdate(&_player);

  BeginDrawing();
  ClearBackground(BLACK);

  DrawAsteroids(_spriteSheet);
  DrawBullets(_spriteSheet);
  PlayerDraw(_player, _spriteSheet);
  DrawScore();

  EndDrawing();
}
