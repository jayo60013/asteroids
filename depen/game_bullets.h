#ifndef GAME_BULLETS_H_
#define GAME_BULLETS_H_

#include "bullet.h"
#include "constants.h"
#include "game_asteroids.h"

void AddBullet(Vector2, float);
void DrawBullets(Texture2D);
void UpdateBullets(void);

bool BulletAsteroidIntersect(Bullet, Asteroid);

#endif
