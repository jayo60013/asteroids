#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define SCREEN_WIDTH 600.f
#define SCREEN_HEIGHT 600.f
#define SCREEN_CENTER                                                          \
  CLITERAL(Vector2) { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f }
#define SCREEN_AREA                                                            \
  CLITERAL(Rectangle) { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }
#define BACKGROUND_COLOUR                                                      \
  CLITERAL(Color) { 15, 15, 15, 255 }

#define MIN_ROTATION_SPEED 5
#define MAX_ROTATION_SPEED 100
#define ASTEROID_LIFE_TIME 10.f
#define ASTEROID_MAX 64
#define ASTEROID_MIN_SPEED 100
#define ASTEROID_MAX_SPEED 300
#define ASTEROID_DELAY 1.25f
#define ASTEROID_DEVIATION SCREEN_WIDTH / 3
#define ASTEROID_BASE_SCORE 10

#define PLAYER_RADIUS 32
#define PLAYER_ROT_SPEED 300.f
#define PLAYER_ACCELERATON 700.f
#define PLAYER_DEACCELERATON 2.f
#define PLAYER_MAX_VEL 500.f
#define PLAYER_FRICTION .99995f
#define PLAYER_FIRE_DELAY .3f
#define PLAYER_NUDGE_VEL 150.f
#define PLAYER_NUM_LIVES 5

#define BULLET_SPEED                                                           \
  CLITERAL(Vector2) { 0.f, 500.f }
#define BULLET_LIFE 2
#define BULLETS_MAX 10
#define BULLET_WIDTH 18
#define BULLET_HEIGHT 26
#define BULLET_COLOR                                                           \
  CLITERAL(Color) { 0, 0, 255, 255 }

#endif
