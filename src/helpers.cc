#include "helpers.h"

// standard library includes
#include <cmath>

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"

void internal_get_offsets(float offsets[2], FoodType foodType) {
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
}

void Helpers::draw_eye(float x, float y, float radius) {
  DrawCircle(x + 0.5F, y + 0.5F, radius, BLACK);
  DrawCircleSector({x, y}, radius / 1.5F, 180.0F, 270.0F, 32, WHITE);
}

void Helpers::draw_blinking_eye(float x, float y, float radius) {
  DrawLineEx({x - radius, y}, {x + radius, y}, BLINKING_EYE_SIZE, BLACK);
}

void Helpers::draw_x_eye(float x, float y, float radius) {
  DrawLineEx({x - radius, y - radius}, {x + radius, y + radius}, X_EYE_SIZE,
             BLACK);
  DrawLineEx({x - radius, y + radius}, {x + radius, y - radius}, X_EYE_SIZE,
             BLACK);
}

void Helpers::draw_open_mouth(float x, float y, float width, float radius,
                              FoodType foodType) {
  float offsets[2];
  internal_get_offsets(offsets, foodType);

  DrawCircle(x + offsets[0] * width, y, radius, BLACK);
}

void Helpers::draw_happy_mouth(float x, float y, float width, float radius,
                               FoodType foodType) {
  float offsets[2];
  internal_get_offsets(offsets, foodType);

  DrawCircleSector({x + offsets[0] * width, y}, radius, -90.0F, 90.0F, 32,
                   BLACK);
}

void Helpers::draw_eyes_full(float x, float y, float width, float height,
                             float radius, FoodType foodType, bool isBlinking,
                             bool isX) {
  float offsets[2];
  internal_get_offsets(offsets, foodType);

  const float eye_width = width * EYE_WIDTH_RATIO;

  if (isX) {
    draw_x_eye(x - eye_width / 2.0F + offsets[0] * width,
               y + offsets[1] * height, radius);
    draw_x_eye(x + eye_width / 2.0F + offsets[0] * width,
               y + offsets[1] * height, radius);
  } else if (isBlinking) {
    draw_blinking_eye(x - eye_width / 2.0F + offsets[0] * width,
                      y + offsets[1] * height, radius);
    draw_blinking_eye(x + eye_width / 2.0F + offsets[0] * width,
                      y + offsets[1] * height, radius);
  } else {
    draw_eye(x - eye_width / 2.0F + offsets[0] * width, y + offsets[1] * height,
             radius);
    draw_eye(x + eye_width / 2.0F + offsets[0] * width, y + offsets[1] * height,
             radius);
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

void Helpers::get_fruit_coords(int coords[4], FoodType foodType) {
  switch (foodType) {
  case FoodType::FT_CORN:
    coords[0] = CORN_COORDS[0];
    coords[1] = CORN_COORDS[1];
    coords[2] = CORN_COORDS[2];
    coords[3] = CORN_COORDS[3];
    break;
  case FoodType::FT_GRAPES:
    coords[0] = GRAPES_COORDS[0];
    coords[1] = GRAPES_COORDS[1];
    coords[2] = GRAPES_COORDS[2];
    coords[3] = GRAPES_COORDS[3];
    break;
  case FoodType::FT_APPLE:
    coords[0] = APPLE_COORDS[0];
    coords[1] = APPLE_COORDS[1];
    coords[2] = APPLE_COORDS[2];
    coords[3] = APPLE_COORDS[3];
    break;
  case FoodType::FT_BROCCOLI:
    coords[0] = BROCCOLI_COORDS[0];
    coords[1] = BROCCOLI_COORDS[1];
    coords[2] = BROCCOLI_COORDS[2];
    coords[3] = BROCCOLI_COORDS[3];
    break;
  case FoodType::FT_BANANA:
    coords[0] = BANANA_COORDS[0];
    coords[1] = BANANA_COORDS[1];
    coords[2] = BANANA_COORDS[2];
    coords[3] = BANANA_COORDS[3];
    break;
  default:
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 0;
    coords[3] = 0;
    break;
  }
}

void Helpers::draw_music_note(float x, float y, float wh, bool enabled) {
  float radiusx = wh * 2.7F / 10.0F;
  DrawEllipse(x + wh / 2.0F, y + wh * 2.0F / 3.0F, radiusx, wh * 2.0F / 10.0F,
              WHITE);
  DrawLineEx({x + wh / 2.0F + radiusx - 2.0F, y + wh / 8.0F},
             {x + wh / 2.0F + radiusx - 2.0F, y + wh * 3.0F / 4.2F}, 4.0F,
             WHITE);
  if (!enabled) {
    draw_x_eye(x + wh / 2.0F, y + wh / 2.0F, wh / 2.0F);
  }
}
