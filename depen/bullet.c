#include "bullet.h"

#include <raylib.h>

Bullet BulletCreate(Vector2 pos, float rot) {
  return (Bullet){
      .pos = pos, .rot = rot, .active = true, .creationTime = GetTime()};
}

void BulletUpdate(Bullet *bullet, float frametime, float time) {
  if (time > bullet->creationTime + BULLET_LIFE ||
      !CheckCollisionPointRec(bullet->pos, SCREEN_AREA)) {
    bullet->active = false;
  }
  if (!bullet->active)
    return;

  Vector2 vel = Vector2Scale(Vector2Rotate(BULLET_SPEED, bullet->rot * DEG2RAD),
                             frametime);
  bullet->pos = Vector2Add(bullet->pos, vel);
}

void BulletDraw(Bullet bullet, Texture2D tex) {
  const Rectangle source = {5, 129, 5, 7};
  Rectangle dest = {bullet.pos.x, bullet.pos.y, BULLET_WIDTH, BULLET_HEIGHT};
  Vector2 origin = {dest.width / 2, dest.height / 2};
  DrawTexturePro(tex, source, dest, origin, bullet.rot, WHITE);
}
