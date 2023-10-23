#include <stdlib.h>
#include <time.h>

#include "depen/constants.h"
#include "depen/game.h"
#include "raylib.h"

void updateDrawFrame(void);

bool _quitGame = false;

int main(void) {
  srand(time(0));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  InitGame();

  while (!WindowShouldClose() && !_quitGame) {
    updateDrawFrame();
  }

  DestroyGame();

  CloseWindow();
  return 0;
}

void updateDrawFrame(void) {
  UpdateGame();

  BeginDrawing();
  ClearBackground(BACKGROUND_COLOUR);

  DrawGame();

  EndDrawing();
}
