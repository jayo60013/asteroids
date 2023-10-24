#include "game_player.h"

static Player _player;
static int _health = PLAYER_NUM_LIVES;

void InitPlayer(void) {
  _player = (Player){.pos = SCREEN_CENTER,
                     .vel = {0.f, 0.f},
                     .acc = {0.f, 0.f},
                     .rot = 180.f,
                     .lastFire = -1.f,
                     .state = PLAYER_DEFAULT};
  _health = PLAYER_NUM_LIVES;
}

static void OnDeath(void) { PlayerSetState(&_player, PLAYER_DEAD); }

static void OnCollision(Asteroid *asteroid) {
  const float playerNudgeMag = 150.f;
  const float asteroidDecel = .4f;

  _health--;
  if (_health <= 0) {
    OnDeath();
    return;
  }

  PlayerSetState(&_player, PLAYER_STUNNED);

  Vector2 nudgeDirection =
      Vector2Normalize(Vector2Subtract(_player.pos, asteroid->pos));
  _player.vel = Vector2Scale(nudgeDirection, playerNudgeMag);

  asteroid->vel = Vector2Scale(asteroid->vel, asteroidDecel);
}

static void TickState(void) {
  const float stunTime = .25f;
  const float iFrameTime = 1.f;
  const float deathDelay = 1.5f;

  switch (_player.state) {
  case PLAYER_DEFAULT:
    break;
  case PLAYER_STUNNED:
    if ((GetTime() - _player.lastStateEntered) > stunTime)
      PlayerSetState(&_player, PLAYER_IFRAME);
    break;
  case PLAYER_IFRAME:
    if ((GetTime() - _player.lastStateEntered) > iFrameTime)
      PlayerSetState(&_player, PLAYER_DEFAULT);
    break;
  case PLAYER_DEAD:
    if ((GetTime() - _player.lastStateEntered) > deathDelay) {
      GameOver();
    }
    break;
  default:
    TraceLog(LOG_ERROR, "Entered unknown state");
  }
}

void DrawPlayer(Texture2D tex) { PlayerDraw(_player, tex); }

void UpdatePlayer(void) {
  TickState();
  PlayerMove(&_player);

  if (_player.state == PLAYER_STUNNED || _player.state == PLAYER_DEAD)
    return;

  PlayerFire(&_player);

  if (_player.state == PLAYER_IFRAME)
    return;

  Asteroid *asteroids = GetAsteroids();

  for (int i = 0; i < ASTEROID_MAX; ++i) {
    Asteroid *asteroid = (asteroids + i);

    if (!asteroid->active)
      continue;

    if (!CheckCollisionCircles(_player.pos, PLAYER_RADIUS, asteroid->pos,
                               AsteroidRadius(*asteroid)))
      continue;

    OnCollision(asteroid);

    break;
  }
}

int GetPlayerHealth() { return _health; }
