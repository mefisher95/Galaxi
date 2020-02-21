#ifndef FLEET_FIRE_H
#define FLEET_FIRE_H

#include <vector>
#include "Surface.h"
#include "Alien_Blue.h"
#include "Alien_Red.h"
#include "Alien_Gold.h"
#include "Alien_Purple.h"
#include "Laser.h"


void fleet_fire(std::vector < Laser> &,
                std::vector < Alien_Blue > &,
                std::vector < Alien_Red > &,
                std::vector < Alien_Gold > &,
                std::vector < Alien_Purple > &,
                int &);

#endif
