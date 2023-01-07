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
      cutTimer(0.0F), cutTimerRateInc(1.0F), postCutTimer(0.0F) {
  flags.set(0);
  flags.set(3);

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
      for (int i = temp.size(); i-- > 0;) {
        scoreString.push_back(temp[i]);
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

  if (flags.test(3)) {
    flags.reset(3);
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
  }

  if (!flags.test(4)) {
    cutTimer += dt * CUT_RATE * cutTimerRateInc;
    if (cutTimer > 1.0F) {
      cutTimer -= 1.0F;
    }
  }

  cutPos = cutTimer * height + offsetY - height / 3.0F;

  if (!flags.test(4) && IsMouseButtonPressed(0)) {
    flags.set(4);
    if (cutPos >= offsetY && cutPos <= offsetY + height / 3.0F) {
      // in correct range
      flags.set(2);
      ++score;
      flags.set(0);
    } else if (cutPos > offsetY + height / 3.0F) {
      // past range
      flags.set(5);
      postCutTimer = POST_CUT_TIME;
    } else {
      // before range
      postCutTimer = POST_CUT_TIME;
    }

    if (flags.test(4) && (flags.test(2) || flags.test(5)) && !flags.test(6)) {
      flags.set(6);
      relativeCutRatio = (cutPos - offsetY) / height;
      splitX = offsetX;
      splitY = offsetY;
      splitAngle = 0.0F;
      splitDX = std::uniform_real_distribution<float>(-SPLIT_DX, SPLIT_DX)(re);
      splitDY = std::uniform_real_distribution<float>(-SPLIT_DY, SPLIT_DY)(re);
      splitDAngle =
          std::uniform_real_distribution<float>(-SPLIT_DA, SPLIT_DA)(re);
      postCutTimer = POST_CUT_TIME;
      cutTimerRateInc += CUT_TIMER_RATE_INC_AMT;
    }
  }

  if (flags.test(6)) {
    splitX += splitDX * dt;
    splitY += splitDY * dt;
    splitAngle += splitDAngle * dt;
  }
  if (postCutTimer > 0.0F) {
    postCutTimer -= dt;
    if (postCutTimer <= 0.0F) {
      reset(!flags.test(2));
    }
  }
}

void Game::draw_impl() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  int coords[4];
  Helpers::get_fruit_coords(coords, (FoodType)currentFood);

  if (flags.test(6)) {
    // bottom portion
    DrawTexturePro(
        spriteSheet,
        {(float)coords[0], (float)coords[1] + coords[3] * relativeCutRatio,
         (float)coords[2], (float)coords[3] * (1.0F - relativeCutRatio)},
        {offsetX, offsetY + height * relativeCutRatio, width,
         height * (1.0F - relativeCutRatio)},
        {0.0F, 0.0F}, 0.0F, WHITE);
    // top portion
    DrawTexturePro(
        spriteSheet,
        {(float)coords[0], (float)coords[1], (float)coords[2],
         (float)coords[3] * relativeCutRatio},
        {splitX + width / 2.0F, splitY + (height * relativeCutRatio / 2.0F),
         width, height * relativeCutRatio},
        {width / 2.0F, height * relativeCutRatio / 2.0F}, splitAngle, WHITE);
  } else {
    DrawTexturePro(spriteSheet,
                   {(float)coords[0], (float)coords[1], (float)coords[2],
                    (float)coords[3]},
                   {offsetX, offsetY, width, height}, {0.0F, 0.0F}, 0.0F,
                   WHITE);
  }

  DrawRectangle(0, offsetY, GetScreenWidth(), height / 3.0F,
                {255, 255, 255, 127});

  DrawLine(0, cutPos, GetScreenWidth(), cutPos, BLACK);

  Helpers::draw_eyes_full(offsetX + width / 2.0F, offsetY + height / 2.0F,
                          width, height, EYE_RADIUS, (FoodType)currentFood,
                          flags.test(1));

  if (flags.test(2)) {
    Helpers::draw_happy_mouth(offsetX + width / 2.0F,
                              offsetY + height / 2.0F * 1.1F, width,
                              MOUTH_RADIUS, (FoodType)currentFood);
  }

  DrawText(scoreString.c_str(), 2, 2, 32, BLACK);
  EndDrawing();
}

void Game::reset(bool wasGameOver) {
  flags.set(0);
  flags.reset(1);
  flags.reset(2);
  flags.set(3);
  flags.reset(4);
  flags.reset(5);
  flags.reset(6);
  if (wasGameOver) {
    score = 0;
    cutTimerRateInc = 1.0F;
  }
  areaSizeRatio = 1.0F;
  unsigned int prevFood = currentFood;
  while (prevFood == currentFood) {
    currentFood = dist(re);
  }
  blinkTimer = 10.0F;
  cutTimer = std::uniform_real_distribution<float>(0.0F, 1.0F)(re);
  postCutTimer = 0.0F;
}
