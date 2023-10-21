#include "player.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "game_bullets.h"

static Vector2 getAcceleration(Player *player) {
  return Vector2Rotate((Vector2){0.f, 1.f}, -player->rot * DEG2RAD);
}

void PlayerMove(Player *player) {
  float frametime = GetFrameTime();
  float time = GetTime();

  if (player->state != PLAYER_STUNNED && player->state != PLAYER_DEAD) {
    UpdateRotation(player, frametime);
    UpdateVelocity(player, frametime);
  }
  UpdatePosition(player, frametime);
  WrapPosition(player);
}

void PlayerFire(Player *player) {
  float time = GetTime();
  Vector2 acc = getAcceleration(player);

  if (IsKeyDown(KEY_SPACE)) {
    if (time > player->lastFire + PLAYER_FIRE_DELAY) {
      AddBullet(Vector2Add(player->pos, Vector2Scale(acc, PLAYER_RADIUS)),
                -player->rot);
      player->lastFire = time;
    }
  }
}

void UpdateVelocity(Player *player, float frametime) {
  int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
  float mag = Vector2Length(player->vel);
  Vector2 acc = getAcceleration(player);

  if (yIn > 0) {
    player->vel = Vector2Add(player->vel,
                             Vector2Scale(acc, PLAYER_ACCELERATON * frametime));
    mag = Vector2Length(player->vel);

    if (mag > PLAYER_MAX_VEL) {
      player->vel = Vector2Scale(Vector2Normalize(player->vel), PLAYER_MAX_VEL);
    }
  } else if (yIn < 0) {
    Vector2 dec = Vector2Scale(player->vel, -1);
    player->vel = Vector2Add(
        player->vel, Vector2Scale(dec, PLAYER_DEACCELERATON * frametime));
  } else {
    player->vel = Vector2Scale(player->vel, PLAYER_FRICTION);
  }
}

void UpdateRotation(Player *player, float frametime) {
  int xIn = (int)IsKeyDown(KEY_LEFT) - (int)IsKeyDown(KEY_RIGHT);
  player->rot += (xIn * PLAYER_ROT_SPEED * frametime);
}

void UpdatePosition(Player *player, float frametime) {
  player->pos = Vector2Add(player->pos, Vector2Scale(player->vel, frametime));
}

void WrapPosition(Player *player) {
  if (player->pos.x < -PLAYER_RADIUS) {
    player->pos.x = SCREEN_WIDTH + PLAYER_RADIUS;

    if (player->vel.x > -PLAYER_NUDGE_VEL) {
      player->vel.x = -PLAYER_NUDGE_VEL;
    }
  } else if (player->pos.x > SCREEN_WIDTH + PLAYER_RADIUS) {
    player->pos.x = -PLAYER_RADIUS;

    if (player->vel.x < PLAYER_NUDGE_VEL) {
      player->vel.x = PLAYER_NUDGE_VEL;
    }
  }
  if (player->pos.y < -PLAYER_RADIUS) {
    player->pos.y = SCREEN_HEIGHT + PLAYER_RADIUS;

    if (player->vel.y > -PLAYER_NUDGE_VEL) {
      player->vel.y = -PLAYER_NUDGE_VEL;
    }
  } else if (player->pos.y > SCREEN_HEIGHT + PLAYER_RADIUS) {
    player->pos.y = -PLAYER_RADIUS;

    if (player->vel.y < PLAYER_NUDGE_VEL) {
      player->vel.y = PLAYER_NUDGE_VEL;
    }
  }
}

void PlayerDraw(Player player, Texture2D tex) {
  Rectangle source = {3, 33, 25, 25};
  Rectangle dest = {player.pos.x, player.pos.y, 64, 64};
  Vector2 origin = {dest.width / 2, dest.height / 2};
  Color playerColor;
  if (player.state == PLAYER_STUNNED) {
    playerColor = RED;
  } else if (player.state == PLAYER_IFRAME) {
    playerColor = PINK;
  } else {
    playerColor = WHITE;
  }

  DrawTexturePro(tex, source, dest, origin, 180 - player.rot, playerColor);

  if (player.state != PLAYER_STUNNED && IsKeyDown(KEY_UP)) {
    source = (Rectangle){74, 46, 8, 16};
    dest = (Rectangle){player.pos.x, player.pos.y, 16, 32};
    origin = (Vector2){dest.width / 2, -25};
    DrawTexturePro(tex, source, dest, origin, 180 - player.rot, WHITE);
  }
}

void PlayerSetState(Player *player, PlayerState state) {
  player->state = state;
  player->lastStateEntered = GetTime();
}
