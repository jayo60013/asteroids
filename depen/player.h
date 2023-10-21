#ifndef PLAYER_H_
#define PLAYER_H_
#include <stdio.h>

#include "constants.h"
#include "raylib.h"

typedef struct Player {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    float rot;
    float lastFire;
} Player;

void PlayerUpdate(Player *);
void UpdateRotation(Player *, float);
void WrapPosition(Player *);
void PlayerDraw(Player, Texture2D);

#endif
