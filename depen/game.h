#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>

#include "game_asteroids.h"
#include "game_bullets.h"
#include "game_player.h"
#include "game_score.h"
#include "game_ui.h"

typedef enum GameState {
  GAME_MAIN_MENU = 0,
  GAME_PLAYING,
  GAME_OVER
} GameState;

void InitGame(void);
void DestroyGame(void);
void UpdateGame(void);
void DrawGame(void);

void GameOver(void);

#endif
