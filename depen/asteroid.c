#include "asteroid.h"

#include "raymath.h"
#include <raylib.h>

Asteroid AsteroidCreate(Vector2 pos, Vector2 vel, AsteroidSize size) {
  return (Asteroid){.active = true,
                    .pos = pos,
                    .vel = vel,
                    .size = size,
                    .rot = GetRandomValue(0, 360),
                    .rotationSpeed =
                        GetRandomValue(MIN_ROTATION_SPEED, MAX_ROTATION_SPEED),
                    .creationTime = GetTime()};
}

void AsteroidUpdate(Asteroid *asteroid, float frametime) {
  if (!asteroid->active)
    return;

  if (GetTime() > asteroid->creationTime + ASTEROID_LIFE_TIME) {
    asteroid->active = false;
    return;
  }

  asteroid->pos =
      Vector2Add(asteroid->pos, Vector2Scale(asteroid->vel, frametime));
  asteroid->rot += asteroid->rotationSpeed * frametime;
}

void AsteroidDraw(Asteroid asteroid, Texture2D tex) {
  if (!asteroid.active)
    return;

  Rectangle source = {62, 189, 60, 60};
  int size = AsteroidRadius(asteroid);
  Rectangle dest = {asteroid.pos.x, asteroid.pos.y, size * 2.f, size * 2.f};
  Vector2 origin = {dest.width / 2, dest.height / 2};
  DrawTexturePro(tex, source, dest, origin, asteroid.rot, WHITE);

  // DEBUG
  // DrawCircleLines(asteroid.pos.x, asteroid.pos.y, size, RED);
}

float AsteroidRadius(Asteroid asteroid) { return 16.f * (int)asteroid.size; }
