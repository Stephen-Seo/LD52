#ifndef LD52_HARVEST_FOOD_CUTS_GAME_H_
#define LD52_HARVEST_FOOD_CUTS_GAME_H_

class Game {
public:
  Game();

  void do_update();

private:

  void update_impl();
  void draw_impl();

};

#endif
