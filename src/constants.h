#ifndef LD52_HARVEST_FOOD_CUTS_CONSTANTS_H_
#define LD52_HARVEST_FOOD_CUTS_CONSTANTS_H_

extern const float PI_F;

constexpr int DEFAULT_SCREEN_WIDTH = 500;
constexpr int DEFAULT_SCREEN_HEIGHT = 800;

constexpr int FOOD_COUNT = 5;

enum class FoodType {
  FT_CORN = 0,
  FT_GRAPES,
  FT_APPLE,
  FT_BROCCOLI,
  FT_BANANA,
};

constexpr int CORN_COORDS[4] = {0, 0, 281, 676};
constexpr int GRAPES_COORDS[4] = {281, 0, 232, 434};
constexpr int APPLE_COORDS[4] = {513, 0, 250, 251};
constexpr int BROCCOLI_COORDS[4] = {767, 2, 268, 153};
constexpr int BANANA_COORDS[4] = {525, 254, 189, 355};

constexpr float CORN_EYE_OFFSET[2] = {-0.01F, 0};
constexpr float GRAPES_EYE_OFFSET[2] = {0, 0};
constexpr float APPLE_EYE_OFFSET[2] = {0, 0};
constexpr float BROCCOLI_EYE_OFFSET[2] = {0, 0};
constexpr float BANANA_EYE_OFFSET[2] = {0.2F, 0};

constexpr float EYE_WIDTH_RATIO = 0.3F;

constexpr float AREA_REDUCTION_SCALE = 0.99F;
constexpr float MIN_AREA = 15.0F;

constexpr float MAX_FOOD_WH = 500.0F;

constexpr float EYE_RADIUS = 14.0F;
constexpr float BLINKING_EYE_SIZE = 4.0F;
constexpr float X_EYE_SIZE = 4.0F;

constexpr float MOUTH_RADIUS = 20.0F;
constexpr float OPEN_MOUTH_RADIUS = 16.0F;

constexpr float MIN_BLINK_TIME = 1.0F;
constexpr float MAX_BLINK_TIME = 20.0F;
constexpr float BLINK_DURATION = 0.7F;

constexpr float CUT_RATE = 0.7F;

constexpr float CUT_TIMER_RATE_INC_AMT = 0.1F;

constexpr float SPLIT_DX = 80.0F;
constexpr float SPLIT_DY = 120.0F;
constexpr float SPLIT_DA = 100.0F;

constexpr float POST_CUT_TIME = 1.7F;

constexpr float MUSIC_NOTE_WH = 80.0F;

#endif
