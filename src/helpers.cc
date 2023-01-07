#include "helpers.h"

// standard library includes
#include <cmath>

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"

void Helpers::draw_eye(float x, float y, float radius) {
  DrawCircle(x + 0.5F, y + 0.5F, radius, BLACK);
  DrawCircleSector({x, y}, radius / 1.5F, 180.0F, 270.0F, 32, WHITE);
}

void Helpers::draw_blinking_eye(float x, float y, float radius) {
  DrawLineEx({x - radius, y}, {x + radius, y}, BLINKING_EYE_SIZE, BLACK);
}

void Helpers::draw_open_mouth(float x, float y, float radius) {
  DrawCircle(x, y, radius, BLACK);
}

void Helpers::draw_happy_mouth(float x, float y, float radius) {
  DrawCircleSector({x, y}, radius, -90.0F, 90.0F, 32, BLACK);
}

void Helpers::draw_eyes_full(float x, float y, float width, float radius,
                             FoodType foodType, bool isBlinking) {
  float offsets[2];
  switch (foodType) {
  case FoodType::FT_CORN:
    offsets[0] = CORN_EYE_OFFSET[0];
    offsets[1] = CORN_EYE_OFFSET[1];
    break;
  case FoodType::FT_GRAPES:
    offsets[0] = GRAPES_EYE_OFFSET[0];
    offsets[1] = GRAPES_EYE_OFFSET[1];
    break;
  case FoodType::FT_APPLE:
    offsets[0] = APPLE_EYE_OFFSET[0];
    offsets[1] = APPLE_EYE_OFFSET[1];
    break;
  case FoodType::FT_BROCCOLI:
    offsets[0] = BROCCOLI_EYE_OFFSET[0];
    offsets[1] = BROCCOLI_EYE_OFFSET[1];
    break;
  case FoodType::FT_BANANA:
    offsets[0] = BANANA_EYE_OFFSET[0];
    offsets[1] = BANANA_EYE_OFFSET[1];
    break;
  default:
    offsets[0] = 0.0F;
    offsets[1] = 0.0F;
    break;
  }

  const float eye_width = width * EYE_WIDTH_RATIO;

  if (isBlinking) {
    draw_blinking_eye(x - eye_width / 2.0F + offsets[0], y + offsets[1],
                      radius);
    draw_blinking_eye(x + eye_width / 2.0F + offsets[0], y + offsets[1],
                      radius);
  } else {
    draw_eye(x - eye_width / 2.0F + offsets[0], y + offsets[1], radius);
    draw_eye(x + eye_width / 2.0F + offsets[0], y + offsets[1], radius);
  }
}

float Helpers::get_cut_pos(float timer, FoodType foodType) {
  switch (foodType) {
  case FoodType::FT_CORN:
    return std::cos(timer) * (float)CORN_COORDS[3];
  case FoodType::FT_GRAPES:
    return std::cos(timer) * (float)GRAPES_COORDS[3];
  case FoodType::FT_APPLE:
    return std::cos(timer) * (float)APPLE_COORDS[3];
  case FoodType::FT_BROCCOLI:
    return std::cos(timer) * (float)BROCCOLI_COORDS[3];
  case FoodType::FT_BANANA:
    return std::cos(timer) * (float)BANANA_COORDS[3];
  }
  return 0.0F;
}
