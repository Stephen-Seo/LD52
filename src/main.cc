// emscripten includes
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

#include "ems.h"
#else
#include <random>
#endif

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"
#include "game.h"

#ifdef __EMSCRIPTEN__
static void *global_game_ptr = nullptr;

EM_BOOL resize_event_callback(int event_type, const EmscriptenUiEvent *event,
                              void *ud) {
  if (event_type == EMSCRIPTEN_EVENT_RESIZE) {
    SetWindowSize(call_js_get_canvas_width(), call_js_get_canvas_height());
  }
  return false;
}
#endif

void game_update(void *game_ptr) { ((Game *)game_ptr)->do_update(); }

int main() {
#ifdef __EMSCRIPTEN__
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
             "LD52_Harvest_Food_Cuts");
#else
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
             "LD52_Harvest_Food_Cuts_Native");
#endif

  Game game{};

#ifdef __EMSCRIPTEN__
  global_game_ptr = &game;

  SetWindowSize(call_js_get_canvas_width(), call_js_get_canvas_height());

  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false,
                                 resize_event_callback);

  emscripten_set_main_loop_arg(game_update, &game, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    game_update(&game);
  }

  CloseAudioDevice();
  CloseWindow();
#endif

  return 0;
}
