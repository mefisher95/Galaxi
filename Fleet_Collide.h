#ifndef FLEET_COLLIDE_H
#define FLEET_COLLIDE_H

#include <vector>
#include "Surface.h"
#include "Player.h"
#include "HUD.h"
#include "Alien_Blue.h"
#include "Alien_Red.h"
#include "Alien_Gold.h"
#include "Alien_Purple.h"
#include "Laser.h"
#include "Explosion.h"

void fleet_collide(std::vector < Laser > &,
                   std::vector < Alien_Blue > &,
                   std::vector < Alien_Red > &,
                   std::vector < Alien_Gold > &,
                   std::vector < Alien_Purple > &,
                   std::vector < Explosion > &,
                   Player &,
                   int);


#endif
