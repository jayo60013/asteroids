#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "asteroid.h"
#include "constants.h"
#include "game_asteroids.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"

void InitPlayer(void);
void DrawPlayer(Texture2D);
void UpdatePlayer(void);
int GetPlayerHealth(void);

#endif
