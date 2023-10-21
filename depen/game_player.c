#include "game_player.h"
#include "player.h"

static Player _player;

void InitPlayer(void) {
  _player = (Player){.pos = SCREEN_CENTER,
                     .vel = {0.f, 0.f},
                     .acc = {0.f, 0.f},
                     .rot = 180.f,
                     .lastFire = -1.f};
}

void DrawPlayer(Texture2D tex) { PlayerDraw(_player, tex); }

void UpdatePlayer(void) { PlayerUpdate(&_player); }
