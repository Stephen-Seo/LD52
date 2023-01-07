#include "game.h"

// third party includes
#include <random>
#include <raylib.h>

// local includes
#include "constants.h"
#include "helpers.h"

Game::Game()
    : re(std::random_device{}()), dist(0, FOOD_COUNT - 1), score(0),
      areaSizeRatio(1.0F), currentFood(dist(re)), blinkTimer(10.0F),
      cutTimer(0.0F), cutTimerRateInc(1.0F) {
  flags.set(0);

  spriteSheet = LoadTexture("resources/produceStuff.png");
}

void Game::do_update() {
  update_impl();
  draw_impl();
}

void Game::update_impl() {
  const float dt = GetFrameTime();

  if (flags.test(0)) {
    flags.set(0);
    scoreString.clear();
    if (score == 0) {
      scoreString.push_back('0');
    } else {
      std::string temp;
      for (unsigned long long i = score; i > 0; i /= 10) {
        temp.push_back((i % 10) + '0');
      }
      for (auto c : temp) {
        scoreString.push_back(c);
      }
    }
  }

  blinkTimer -= dt;
  if (blinkTimer <= 0.0F) {
    flags.flip(1);
    if (flags.test(1)) {
      blinkTimer = BLINK_DURATION;
    } else {
      blinkTimer = std::uniform_real_distribution<float>{MIN_BLINK_TIME,
                                                         MAX_BLINK_TIME}(re);
    }
  }

  cutTimer += dt * CUT_TIMER_RATE * cutTimerRateInc;
  if (cutTimer > 1.0F) {
    cutTimer -= 1.0F;
  }
}

void Game::draw_impl() {

  BeginDrawing();
  ClearBackground(RAYWHITE);

  float ratio;
  float width;
  float height;
  float offsetX;
  float offsetY;

  switch (currentFood) {
  case (unsigned int)FoodType::FT_APPLE:
    ratio = (float)APPLE_COORDS[2] / (float)APPLE_COORDS[3];
    break;
  case (unsigned int)FoodType::FT_BANANA:
    ratio = (float)BANANA_COORDS[2] / (float)BANANA_COORDS[3];
    break;
  case (unsigned int)FoodType::FT_BROCCOLI:
    ratio = (float)BROCCOLI_COORDS[2] / (float)BROCCOLI_COORDS[3];
    break;
  case (unsigned int)FoodType::FT_CORN:
    ratio = (float)CORN_COORDS[2] / (float)CORN_COORDS[3];
    break;
  case (unsigned int)FoodType::FT_GRAPES:
    ratio = (float)GRAPES_COORDS[2] / (float)GRAPES_COORDS[3];
    break;
  default:
    ratio = 1.0F;
    break;
  }

  if (ratio < 1.0F) {
    height = MAX_FOOD_WH;
    width = height * ratio;
  } else {
    width = MAX_FOOD_WH;
    height = width / ratio;
  }

  if (width > GetScreenWidth() && height <= GetScreenHeight()) {
    if (ratio < 1.0F) {
      height = GetScreenWidth() / ratio;
      width = height * ratio;
    } else {
      width = GetScreenWidth();
      height = width / ratio;
    }
  } else if (width <= GetScreenWidth() && height > GetScreenHeight()) {
    if (ratio < 1.0F) {
      height = GetScreenHeight();
      width = height * ratio;
    } else {
      width = GetScreenHeight() * ratio;
      height = width / ratio;
    }
  }
  offsetX = (GetScreenWidth() - width) / 2.0F;
  offsetY = (GetScreenHeight() - height) / 2.0F;

  switch (currentFood) {
  case (unsigned int)FoodType::FT_APPLE:
    DrawTexturePro(
        spriteSheet,
        {APPLE_COORDS[0], APPLE_COORDS[1], APPLE_COORDS[2], APPLE_COORDS[3]},
        {offsetX, offsetY, width, height}, {0.0F, 0.0F}, 0.0F, WHITE);
    break;
  case (unsigned int)FoodType::FT_BANANA:
    DrawTexturePro(spriteSheet,
                   {BANANA_COORDS[0], BANANA_COORDS[1], BANANA_COORDS[2],
                    BANANA_COORDS[3]},
                   {offsetX, offsetY, width, height}, {0.0F, 0.0F}, 0.0F,
                   WHITE);
    break;
  case (unsigned int)FoodType::FT_BROCCOLI:
    DrawTexturePro(spriteSheet,
                   {BROCCOLI_COORDS[0], BROCCOLI_COORDS[1], BROCCOLI_COORDS[2],
                    BROCCOLI_COORDS[3]},
                   {offsetX, offsetY, width, height}, {0.0F, 0.0F}, 0.0F,
                   WHITE);
    break;
  case (unsigned int)FoodType::FT_CORN:
    DrawTexturePro(
        spriteSheet,
        {CORN_COORDS[0], CORN_COORDS[1], CORN_COORDS[2], CORN_COORDS[3]},
        {offsetX, offsetY, width, height}, {0.0F, 0.0F}, 0.0F, WHITE);
    break;
  case (unsigned int)FoodType::FT_GRAPES:
    DrawTexturePro(spriteSheet,
                   {GRAPES_COORDS[0], GRAPES_COORDS[1], GRAPES_COORDS[2],
                    GRAPES_COORDS[3]},
                   {offsetX, offsetY, width, height}, {0.0F, 0.0F}, 0.0F,
                   WHITE);
    break;
  default:
    break;
  }

  DrawRectangle(0, offsetY, GetScreenWidth(), height / 3.0F,
                {255, 255, 255, 127});

  float cutPos = cutTimer * height;

  DrawLine(0, cutPos + offsetY - height / 3.0F, GetScreenWidth(),
           cutPos + offsetY - height / 3.0F, BLACK);

  Helpers::draw_eyes_full(offsetX + width / 2.0F, offsetY + height / 2.0F,
                          width, EYE_RADIUS, (FoodType)currentFood,
                          flags.test(1));

  if (flags.test(2)) {
    Helpers::draw_happy_mouth(offsetX + width / 2.0F, offsetY + height / 2.0F,
                              MOUTH_RADIUS);
  }

  DrawText(scoreString.c_str(), 2, 2, 32, BLACK);
  EndDrawing();
}

void Game::reset() {
  flags.set(0);
  score = 0;
  areaSizeRatio = 1.0F;
  currentFood = dist(re);
  blinkTimer = 10.0F;
  cutTimer = 0.0F;
}
