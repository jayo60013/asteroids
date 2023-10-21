#ifndef GAME_ASTEROIDS_H_
#define GAME_ASTEROIDS_H_

#include "asteroid.h"
#include "game_score.h"

void AddAsteroid(AsteroidSize);
void AddAsteroidWithPos(Vector2, Vector2, AsteroidSize);
void DrawAsteroids(Texture2D);
void UpdateAsteroids(void);

Vector2 GetNextAsteroidPos(void);
Vector2 GetNextAsteroidVel(Vector2);

Asteroid *GetAsteroids(void);
void DestroyAsteroid(int index);

#endif
