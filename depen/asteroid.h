#ifndef ASTROID_H
#define ASTROID_H

#include "constants.h"
#include "raylib.h"

typedef enum AsteroidSize {
  ASTEROID_SMALL = 2,
  ASTEROID_MEDIUM = 3,
  ASTEROID_LARGE = 4
} AsteroidSize;

typedef struct Asteroid {
  bool active;
  Vector2 pos;
  Vector2 vel;

  AsteroidSize size;

  float rot;
  float rotationSpeed;
  float creationTime;

} Asteroid;

Asteroid AsteroidCreate(Vector2, Vector2, AsteroidSize);
void AsteroidUpdate(Asteroid *asteroid, float frametime);
void AsteroidDraw(Asteroid asteroid, Texture2D tex);
float AsteroidRadius(Asteroid);

#endif
