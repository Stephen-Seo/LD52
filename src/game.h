#ifndef LD52_HARVEST_FOOD_CUTS_GAME_H_
#define LD52_HARVEST_FOOD_CUTS_GAME_H_

// standard library includes
#include <bitset>
#include <random>

// third party includes
#include <raylib.h>

class Game {
public:
  Game();

  void do_update();

private:
  void update_impl();
  void draw_impl();

  void reset(bool wasGameOver);

  std::default_random_engine re;
  std::uniform_int_distribution<unsigned int> dist;
  std::string scoreString;
  Texture2D spriteSheet;
  unsigned long long score;
  /*
   * 0 - score dirty
   * 1 - is blinking
   * 2 - happy
   * 3 - fruit dirty
   * 4 - cut has happened
   * 5 - sad
   * 6 - relativeCutPos is set
   */
  std::bitset<32> flags;
  float areaSizeRatio;
  float currentArea;
  unsigned int currentFood;
  float blinkTimer;
  float cutTimer;
  float cutTimerRateInc;
  float ratio;
  float width;
  float height;
  float offsetX;
  float offsetY;
  float cutPos;
  float relativeCutRatio;
  float splitX;
  float splitY;
  float splitAngle;
  float splitDX;
  float splitDY;
  float splitDAngle;
  float postCutTimer;
};

#endif
