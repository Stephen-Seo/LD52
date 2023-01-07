#include "game.h"

// third party includes
#include <raylib.h>

Game::Game() {}

void Game::do_update() {
  update_impl();
  draw_impl();
}

void Game::update_impl() {}

void Game::draw_impl() {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("Testing...", 100, 100, 30, RAYWHITE);
  EndDrawing();
}
