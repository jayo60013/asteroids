#include "game_score.h"
#include <raylib.h>

static int _score = 0;

void ResetScore() { _score = 0; }
void AddScore(int score) { _score += score; }
void DrawScore(void) {
  const int fontSize = 32;
  const Color black = Fade(BLACK, .8f);
  const Color white = Fade(WHITE, .8f);

  const int xPadding = 16;
  const int yPadding = 8;
  const int shadow = 4;

  const char *scoreText = TextFormat("%d PTS", _score);
  int textLength = MeasureText(scoreText, fontSize);

  int x = SCREEN_WIDTH - textLength - xPadding;
  int y = yPadding;

  DrawText(scoreText, x + shadow, y + shadow, fontSize, black);
  DrawText(scoreText, x, y, fontSize, white);
}
