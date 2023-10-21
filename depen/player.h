#ifndef PLAYER_H_
#define PLAYER_H_
#include <stdio.h>

#include "constants.h"
#include "raylib.h"

typedef enum PlayerState {
  PLAYER_DEFAULT = 0,
  PLAYER_STUNNED,
  PLAYER_IFRAME,
  PLAYER_DEAD
} PlayerState;

typedef struct Player {
  Vector2 pos;
  Vector2 vel;
  Vector2 acc;
  float rot;
  float lastFire;
  PlayerState state;
  float lastStateEntered;
} Player;

void PlayerMove(Player *);
void UpdateRotation(Player *, float);
void UpdateVelocity(Player *, float);
void UpdatePosition(Player *, float);
void WrapPosition(Player *);
void PlayerDraw(Player, Texture2D);
void PlayerFire(Player *);

void PlayerSetState(Player *player, PlayerState state);

#endif
