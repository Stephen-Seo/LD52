#ifndef LD52_HARVEST_FOOD_CUTS_H_
#define LD52_HARVEST_FOOD_CUTS_H_

#include "constants.h"

namespace Helpers {

extern void draw_eye(float x, float y, float radius);
extern void draw_blinking_eye(float x, float y, float radius);
extern void draw_x_eye(float x, float y, float radius);
extern void draw_open_mouth(float x, float y, float width, float radius,
                            FoodType foodType);
extern void draw_happy_mouth(float x, float y, float width, float radius,
                             FoodType foodType);

extern void draw_eyes_full(float x, float y, float width, float height,
                           float radius, FoodType foodType, bool isBlinking,
                           bool isX);

extern float get_cut_pos(float timer, FoodType foodType);

extern void get_fruit_coords(int coords[4], FoodType foodType);

extern void draw_music_note(float x, float y, float wh, bool enabled);

} // namespace Helpers

#endif
