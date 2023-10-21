#include "game_asteroids.h"

#include "constants.h"
#include "raymath.h"

static AsteroidSize _sizes[3] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                 ASTEROID_LARGE};
static Asteroid _asteroids[ASTEROID_MAX] = {0};
static float _lastCreationTime = -1.f;

void AddAsteroid(AsteroidSize size) {
  Vector2 pos = GetNextAsteroidPos();
  Vector2 vel = GetNextAsteroidVel(pos);

  for (int i = 0; i < ASTEROID_MAX; ++i) {
    if (!_asteroids[i].active) {
      _asteroids[i] = CreateAsteroid(pos, vel, size);
      return;
    }
  }

  TraceLog(LOG_ERROR, "Failed to create an asteroid");
}

void AddAsteroidWithPos(Vector2 pos, Vector2 vel, AsteroidSize size) {
  for (int i = 0; i < ASTEROID_MAX; ++i) {
    if (!_asteroids[i].active) {
      _asteroids[i] = CreateAsteroid(pos, vel, size);
      return;
    }
  }

  TraceLog(LOG_ERROR, "Failed to create an asteroid");
}

void UpdateAsteroids() {
  float frametime = GetFrameTime();
  float time = GetTime();

  for (int i = 0; i < ASTEROID_MAX; ++i) {
    AsteroidUpdate(_asteroids + i, frametime);
  }

  if (time > _lastCreationTime + ASTEROID_DELAY) {
    AsteroidSize size = _sizes[GetRandomValue(0, 2)];
    AddAsteroid(size);
    _lastCreationTime = time;
  }
}

void DrawAsteroids(Texture2D spriteSheet) {
  for (int i = 0; i < ASTEROID_MAX; ++i) {
    AsteroidDraw(_asteroids[i], spriteSheet);
  }
}
/* Create a circle around the game screen, the position will be a random point
 * on this circle*/
Vector2 GetNextAsteroidPos(void) {
  float r =
      (SCREEN_WIDTH > SCREEN_HEIGHT) ? (float)SCREEN_WIDTH : SCREEN_HEIGHT;
  float theta = DEG2RAD * (float)GetRandomValue(0, 359);
  Vector2 pos = {SCREEN_CENTER.x + r * cosf(theta),
                 SCREEN_CENTER.y + r * sinf(theta)};
  return pos;
}

/* Create a smaller cirlce centered around screen middle, draw a line between
 * the position and a point on the circle to get a line pointing towards the
 * middle of the screen */
Vector2 GetNextAsteroidVel(Vector2 pos) {
  float r = (float)ASTEROID_DEVIATION;

  float theta = DEG2RAD * (float)GetRandomValue(0, 359);
  Vector2 vel = {SCREEN_CENTER.x + r * cosf(theta),
                 SCREEN_CENTER.y + r * sinf(theta)};

  vel = Vector2Subtract(vel, pos);
  vel = Vector2Normalize(vel);
  vel = Vector2Scale(
      vel, (float)GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));

  return vel;
}

Asteroid *GetAsteroids(void) { return _asteroids; }

void DestroyAsteroid(int index) {
  Asteroid *asteroid = _asteroids + index;
  asteroid->active = false;

  Vector2 newVel = Vector2Scale(asteroid->vel, 0.5f);
  int points = (int)asteroid->size * ASTEROID_BASE_SCORE;

  switch (asteroid->size) {
  case ASTEROID_LARGE:
    AddAsteroidWithPos(asteroid->pos, Vector2Rotate(newVel, 90.f * DEG2RAD),
                       ASTEROID_MEDIUM);
    AddAsteroidWithPos(asteroid->pos, Vector2Rotate(newVel, -90.f * DEG2RAD),
                       ASTEROID_MEDIUM);
    break;
  case ASTEROID_MEDIUM:
    AddAsteroidWithPos(asteroid->pos, Vector2Rotate(newVel, 90.f * DEG2RAD),
                       ASTEROID_SMALL);
    AddAsteroidWithPos(asteroid->pos, Vector2Rotate(newVel, -90.f * DEG2RAD),
                       ASTEROID_SMALL);
    break;
  case ASTEROID_SMALL:
    break;
  }

  AddScore(points);
}
