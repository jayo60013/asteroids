#include "game_bullets.h"
#include "constants.h"
#include <raylib.h>

static Bullet _bullets[BULLETS_MAX];

void AddBullet(Vector2 pos, float rot) {
  for (int i = 0; i < BULLETS_MAX; ++i) {
    if (_bullets[i].active)
      continue;

    _bullets[i] = BulletCreate(pos, rot);
    return;
  }
}

void UpdateBullets(void) {
  float frametime = GetFrameTime();
  float time = GetTime();

  Asteroid *asteroids = GetAsteroids();

  for (int i = 0; i < BULLETS_MAX; ++i) {
    if (_bullets[i].active) {
      BulletUpdate(_bullets + i, frametime, time);

      for (int j = 0; j < ASTEROID_MAX; ++j) {
        if (!(asteroids + j)->active)
          continue;
        if (BulletAsteroidIntersect(_bullets[i], *(asteroids + j))) {
          (_bullets + i)->active = false;
          DestroyAsteroid(j);
          break;
        }
      }
    }
  }
}

void DrawBullets(Texture2D spriteSheet) {
  for (int i = 0; i < BULLETS_MAX; ++i) {
    if (_bullets[i].active)
      BulletDraw(_bullets[i], spriteSheet);
  }
}

bool BulletAsteroidIntersect(Bullet b, Asteroid a) {
  float asteroidRadius = AsteroidRadius(a);

  return CheckCollisionPointCircle(b.pos, a.pos, asteroidRadius);
}

void ResetBullets(void) {
  for (int i = 0; i < BULLETS_MAX; i++) {
    _bullets[i] = (Bullet){0};
  }
}
