#!/bin/sh

# emcc -o demo.html main.c -Wall -std=c99 \
#   -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os \
#   -I. -I /home/jay/docs/projects/cpp/raylib/src -I /home/jay/docs/projects/cpp/raylib/src/external \
#   -L. -L /home/jay/docs/projects/cpp/raylib/src \
#   -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 \
#   --shell-file /home/jay/docs/projects/cpp/raylib/src/shell.html /home/jay/docs/projects/cpp/raylib/src/web/libraylib.a \
#   -DPLATFORM_WEB -s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main"]' -s EXPORTED_RUNTIME_METHODS=ccall

emcc -o asteroids.html main.c depen/asteroid.c depen/bullet.c depen/game_asteroids.c depen/game_bullets.c depen/game.c depen/game_player.c depen/game_score.c depen/game_ui.c depen/player.c \
  -std=c99 \
  -Os \
  -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' \
  --preload-file assets \
  -s ALLOW_MEMORY_GROWTH=1 \
  -I. -I /home/jay/docs/projects/cpp/raylib/src -I /home/jay/docs/projects/cpp/raylib/src/external \
  -I/home/jay/docs/projects/cpp/raylib \
  -L. -L /home/jay/docs/projects/cpp/raylib/src \
  -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 \
  --shell-file /home/jay/docs/projects/cpp/raylib/src/shell.html /home/jay/docs/projects/cpp/raylib/src/web/libraylib.a \
  -DPLATFORM_WEB -s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main"]' -s EXPORTED_RUNTIME_METHODS=ccall
