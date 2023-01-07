#ifndef LD52_HARVEST_FOOD_CUTS_H_
#define LD52_HARVEST_FOOD_CUTS_H_

#include "constants.h"

namespace Helpers {

extern void draw_eye(float x, float y, float radius);
extern void draw_blinking_eye(float x, float y, float radius);
extern void draw_open_mouth(float x, float y, float radius);
extern void draw_happy_mouth(float x, float y, float radius);

extern void draw_eyes_full(float x, float y, float width, float radius,
                           FoodType foodType, bool isBlinking);

extern float get_cut_pos(float timer, FoodType foodType);

} // namespace Helpers

#endif
