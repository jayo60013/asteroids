#include "player.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "game_bullets.h"

void PlayerUpdate(Player *player) {
    float frametime = GetFrameTime();
    float time = GetTime();

    UpdateRotation(player, frametime);

    int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
    float mag = Vector2Length(player->vel);
    Vector2 acc = Vector2Rotate((Vector2){0.f, 1.f}, -player->rot * DEG2RAD);

    if (yIn > 0) {
        player->vel = Vector2Add(
            player->vel, Vector2Scale(acc, PLAYER_ACCELERATON * frametime));
        mag = Vector2Length(player->vel);

        if (mag > PLAYER_MAX_VEL) {
            player->vel =
                Vector2Scale(Vector2Normalize(player->vel), PLAYER_MAX_VEL);
        }
    } else if (yIn < 0) {
        Vector2 dec = Vector2Scale(player->vel, -1);
        player->vel = Vector2Add(
            player->vel, Vector2Scale(dec, PLAYER_DEACCELERATON * frametime));
    } else {
        player->vel = Vector2Scale(player->vel, PLAYER_FRICTION);
    }

    player->pos = Vector2Add(player->pos, Vector2Scale(player->vel, frametime));
    WrapPosition(player);

    if (IsKeyDown(KEY_SPACE)) {
        if (time > player->lastFire + PLAYER_FIRE_DELAY) {
            AddBullet(Vector2Add(player->pos, Vector2Scale(acc, PLAYER_RADIUS)),
                      -player->rot);
            player->lastFire = time;
        }
    }
}

void UpdateRotation(Player *player, float frametime) {
    int xIn = (int)IsKeyDown(KEY_LEFT) - (int)IsKeyDown(KEY_RIGHT);
    player->rot += (xIn * PLAYER_ROT_SPEED * frametime);
}

void WrapPosition(Player *player) {
    if (player->pos.x < -PLAYER_RADIUS) {
        player->pos.x = SCREEN_WIDTH + PLAYER_RADIUS;
    } else if (player->pos.x > SCREEN_WIDTH + PLAYER_RADIUS) {
        player->pos.x = -PLAYER_RADIUS;
    }
    if (player->pos.y < -PLAYER_RADIUS) {
        player->pos.y = SCREEN_HEIGHT + PLAYER_RADIUS;
    } else if (player->pos.y > SCREEN_HEIGHT + PLAYER_RADIUS) {
        player->pos.y = -PLAYER_RADIUS;
    }
}

void PlayerDraw(Player player, Texture2D tex) {
    Rectangle source = {3, 33, 25, 25};
    Rectangle dest = {player.pos.x, player.pos.y, 64, 64};
    Vector2 origin = {dest.width / 2, dest.height / 2};
    DrawTexturePro(tex, source, dest, origin, 180 - player.rot, WHITE);

    if (IsKeyDown(KEY_UP)) {
        source = (Rectangle){74, 46, 8, 16};
        dest = (Rectangle){player.pos.x, player.pos.y, 16, 32};
        origin = (Vector2){dest.width / 2, -25};
        DrawTexturePro(tex, source, dest, origin, 180 - player.rot, WHITE);
    }
}
