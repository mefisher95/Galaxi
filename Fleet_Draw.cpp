#include "Fleet_Draw.h"

void draw_blue(std::vector < Alien_Blue > &, int);
void draw_red(std::vector < Alien_Red > &, int);
void draw_gold(std::vector < Alien_Gold > &, int);
void draw_purple(std::vector < Alien_Purple > &, int);


void fleet_draw(Surface & surface,
                std::vector < Alien_Blue > & fleet_blue,
                std::vector < Alien_Red > & fleet_red,
                std::vector < Alien_Gold> & fleet_gold,
                std::vector < Alien_Purple > & fleet_purple, int i)
{
    if (i < 22) draw_blue(fleet_blue, i);
    if (i < 9)  draw_red(fleet_red, i);
    if (i < 3)  draw_gold(fleet_gold, i);
    if (i < 6)  draw_purple(fleet_purple, i);
}

void draw_blue(std::vector < Alien_Blue > & fleet_blue, int i)
{
    fleet_blue[i].draw();
}

void draw_red(std::vector < Alien_Red > & fleet_red, int i)
{
    fleet_red[i].draw();
}

void draw_gold(std::vector < Alien_Gold > & fleet_gold, int i)
{
    fleet_gold[i].draw();
}

void draw_purple(std::vector < Alien_Purple > & fleet_purple, int i)
{
    fleet_purple[i].draw();
}
