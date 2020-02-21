#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include <vector>
#include "Includes.h"
#include "Constants.h"
#include "Alien_Blue.h"
#include "Alien_Red.h"
#include "Alien_Gold.h"
#include "Alien_Purple.h"
#include "Stars.h"
#include "Laser.h"
#include "HUD.h"
#include "Explosion.h"


void main_menu(Surface &, Event &, Galaxy &, KeyPressed &,
               bool &, bool &, bool &, bool &, std::vector < int > &);
void game_rules(Surface &, KeyPressed &, Event &, Galaxy &, bool &, bool &);
void high_score(Surface &, KeyPressed &, Event &, Galaxy &, bool &, std::vector < int > &);
void end_game(Surface &, KeyPressed &, Event &, bool &);

void build_laser_array(Surface &, std::vector < Laser > &);
void laser_array_move(std::vector < Laser > &, int);
void laser_array_draw(std::vector < Laser > &, int);

void fire(std::vector < Laser > &, KeyPressed &, Player &);

bool collision(std::vector < Laser > & laser_array, Player &,
               std::vector < Explosion > &, int);
bool collision(std::vector < Alien_Gold > & alien, Player & player, int);
bool collision(std::vector < Alien_Red > & alien, Player & player, int);
bool collision(std::vector < Alien_Blue > & alien, Player & player, int);

void rebirth(std::vector < Alien_Blue > &, std::vector < Alien_Red > &,
             std::vector < Alien_Gold > &, std::vector < Alien_Purple > &, int);
void reposition(std::vector < Alien_Blue > &, std::vector < Alien_Red > &,
                std::vector < Alien_Gold > &, std::vector < Alien_Purple > &,
                int);

#endif
