#include "ems.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

EM_JS(int, canvas_get_width, (),
      { return document.getElementById("canvas").clientWidth; });

EM_JS(int, canvas_get_height, (),
      { return document.getElementById("canvas").clientHeight; });
#else
#include <iostream>
#endif

int call_js_get_canvas_width() {

#ifdef __EMSCRIPTEN__
  return canvas_get_width();
#else
  return 800;
#endif
}

int call_js_get_canvas_height() {
#ifdef __EMSCRIPTEN__
  return canvas_get_height();
#else
  return 500;
#endif
}
