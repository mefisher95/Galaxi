#include "Fleet_Move.h"

void move_blue(int, std::vector < Alien_Blue > &, int);
void move_red(int, std::vector < Alien_Red > &, int);
void move_gold(int, std::vector < Alien_Gold > &, int);
void move_purple(int, std::vector < Alien_Purple > &, int);

void fleet_move(int & direction,
                 std::vector < Alien_Blue > & fleet_blue,
                 std::vector < Alien_Red > & fleet_red,
                 std::vector < Alien_Gold> & fleet_gold,
                 std::vector < Alien_Purple > & fleet_purple)
{
    if (fleet_blue[0].x() <= 0) direction = -direction; 
    if (fleet_blue[10].x() >= W - fleet_blue[0].w() - 10) direction = -direction;

    for (int i = 0; i < 22; ++i)
    {
        move_blue(direction, fleet_blue, i);
        if (i < 9) move_red(direction, fleet_red, i);
        if (i < 3)move_gold(direction, fleet_gold, i);
        if (i < 6)move_purple(direction, fleet_purple, i);
    }
}

void move_blue(int direction, std::vector < Alien_Blue > & fleet_blue, int i)
{
    fleet_blue[i].move(direction);
}

void move_red(int direction, std::vector < Alien_Red > & fleet_red, int i)
{   
   
    fleet_red[i].move(direction);
}

void move_gold(int direction, std::vector < Alien_Gold > & fleet_gold, int i)
{
    fleet_gold[i].move(direction);
}

void move_purple(int direction, std::vector < Alien_Purple > & fleet_purple, int i)
{
    fleet_purple[i].move(direction);
}
