#ifndef FLEET_MOVE_H
#define FLEET_MOVE_H

#include <vector>
#include "Surface.h"
#include "Alien_Blue.h"
#include "Alien_Red.h"
#include "Alien_Gold.h"
#include "Alien_Purple.h"

void fleet_move(int & direction,
                std::vector < Alien_Blue > &,
                std::vector < Alien_Red > &,
                std::vector < Alien_Gold> &,
                std::vector < Alien_Purple > &);

#endif
