#include "game_ui.h"
#include "constants.h"
#include "game_player.h"
#include <raylib.h>

void DrawHealthBar() {
  const Color healthHigh = GREEN;
  const Color healthMedium = YELLOW;
  const Color healthLow = RED;

  const int cellWidth = SCREEN_HEIGHT / 15;
  const int cellHeight = SCREEN_HEIGHT / 30;

  int health = GetPlayerHealth();
  float barWidth = cellWidth * health;

  Rectangle r =
      (Rectangle){SCREEN_WIDTH / 2 - (PLAYER_NUM_LIVES * cellWidth * .5f),
                  SCREEN_HEIGHT - cellWidth * 1.5f, barWidth, cellHeight};
  DrawRectangleRoundedLines(r, .25f, 16, 10, BLACK);

  Color c;
  if (health >= PLAYER_NUM_LIVES * .6f) {
    c = healthHigh;
  } else if (health >= PLAYER_NUM_LIVES * .25f) {
    c = healthMedium;
  } else {
    c = healthLow;
  }

  DrawRectangleRec(r, c);
  for (int x = r.x; x < r.x + r.width; x += r.width / health) {
    Vector2 start = {x, r.y};
    Vector2 end = {x, r.y + r.height};
    int lineThickness = 4;
    DrawLineEx(start, end, lineThickness, BLACK);
  }
}
