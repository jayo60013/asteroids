#include "game_bullets.h"
#include <raylib.h>

static Bullet _bullets[BULLETS_MAX];

void AddBullet(Vector2 pos, float rot) {
  for (int i = 0; i < BULLETS_MAX; ++i) {
    if (_bullets[i].active)
      continue;

    _bullets[i] = CreateBullet(pos, rot);
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
  Rectangle bulletRect = {b.pos.x - BULLET_WIDTH / 2.f,
                          b.pos.y - BULLET_HEIGHT / 2.f, BULLET_WIDTH / 2.f,
                          BULLET_HEIGHT / 2.f};
  float asteroidRadius = AsteroidRadius(a);
  Vector2 asteroidCenter = {a.pos.x - asteroidRadius / 2.f,
                            a.pos.y - asteroidRadius / 2.f};

  float testX = asteroidCenter.x;
  float testY = asteroidCenter.y;

  if (asteroidCenter.x < bulletRect.x)
    testX = bulletRect.x;
  else if (asteroidCenter.x > bulletRect.x + bulletRect.width)
    testX = bulletRect.x + bulletRect.width;
  if (asteroidCenter.y < bulletRect.y)
    testY = bulletRect.y;
  else if (asteroidCenter.y > bulletRect.y + bulletRect.height)
    testY = bulletRect.y + bulletRect.height;

  float distX = asteroidCenter.x - testX;
  float distY = asteroidCenter.y - testY;
  float distance = sqrt((distX * distX) + (distY * distY));

  if (distance <= asteroidRadius) {
    return true;
  }
  return false;
}
