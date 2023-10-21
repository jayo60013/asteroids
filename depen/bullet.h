#ifndef BULLET_H_
#define BULLET_H_

#include <raylib.h>
#include <raymath.h>

#include "constants.h"

typedef struct Bullet {
    bool active;
    Vector2 pos;
    float rot;
    float creationTime;
} Bullet;

Bullet CreateBullet(Vector2, float);
void BulletUpdate(Bullet *, float, float);
void BulletDraw(Bullet, Texture2D);

#endif