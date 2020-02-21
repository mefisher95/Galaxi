#include "Fleet_Build.h"


void build_blue(Surface &, std::vector < Alien_Blue > &, int);
void build_red(Surface &, std::vector < Alien_Red > &, int);
void build_gold(Surface &, std::vector < Alien_Gold > &, int);
void build_purple(Surface &, std::vector < Alien_Purple > &, int);


void fleet_build(Surface & surface,
                 std::vector < Alien_Blue > & fleet_blue,
                 std::vector < Alien_Red > & fleet_red,
                 std::vector < Alien_Gold > & fleet_gold,
                 std::vector < Alien_Purple > & fleet_purple)
{
    Alien_Blue alien(surface, true);
    int row_count = 11;
    int space_count = row_count - 1;
    int width = row_count * alien.w() + space_count * 10;

    build_blue(surface, fleet_blue, width);
    build_red(surface, fleet_red, width);
    build_gold(surface, fleet_gold, width);
    build_purple(surface, fleet_purple, width);
    fleet_blue[0].set_num(22);
    fleet_red[0].set_num(9);
    fleet_gold[0].set_num(3);
    fleet_purple[0].set_num(6);
}


void build_blue(Surface & surface, std::vector < Alien_Blue > & fleet_blue, int width)
{
    int max_aliens = 22;
    
    for (int i = 0; i < max_aliens; ++i)
    {
        Alien_Blue alien(surface, true);
        
        if (i == 0)
        {            
            alien.x(width / 2);
            alien.y(200);
        }
        else if (i < 11)
        {
            alien.x(fleet_blue[i - 1].x() + fleet_blue[i - 1].w() + 10);
            alien.y(fleet_blue[0].y());
        }
        else if (i == 11)
        {
            alien.x(fleet_blue[0].x());
            alien.y(fleet_blue[0].y() + fleet_blue[0].h() + 10);
        }
        else if (i < 22)
        {
            alien.x(fleet_blue[i - 1].x() + fleet_blue[i - 1].w() + 10);
            alien.y(fleet_blue[11].y());
        }
        
        fleet_blue.push_back(alien);
    }
    fleet_blue.shrink_to_fit();
}


void build_red(Surface & surface, std::vector < Alien_Red > & fleet_red,
               int width)
{
    int max_aliens = 9;
    
    for (int i = 0; i < max_aliens; ++i)
    {
        Alien_Red alien(surface, true);
        if (i == 0)
        {
            alien.x((width / 2) + alien.w() + 10);
            alien.y(125);
        }
        else if (i < 3)
        {
            alien.x(fleet_red[i - 1].x() + fleet_red[i - 1].w() + 40 + (alien.w() * 3));
            alien.y(fleet_red[0].y());
        }
        else if (i == 3)
        {
            alien.x(width / 2);
            alien.y(90);
        }
        else if (i == 4)
        {
            alien.x((width / 2) + 2 * alien.w() + 20);
            alien.y(90);
        }
        else if (i == 5)
        {
            alien.x((width / 2) + 40 + (alien.w() * 4));
            alien.y(90);
        }
        else if (i == 6)
        {
            alien.x(fleet_red[i - 1].x() + 2 * (fleet_red[i - 1].w() + 10));
            alien.y(90);
        }

        else if (i == 7)
        {
            alien.x(fleet_red[i - 1].x() + 2 * (fleet_red[i - 1].w() + 10));
            alien.y(90);
        }
        else if (i == 8)
        {
            alien.x(fleet_red[i - 1].x() + 2 * (fleet_red[i - 1].w() + 10));
            alien.y(90);
        }
        
        fleet_red.push_back(alien);
    }
    fleet_red.shrink_to_fit();
}


void build_gold(Surface & surface, std::vector < Alien_Gold > & fleet_gold,
                int width)
{
    int max_aliens = 3;
    
    for (int i = 0; i < max_aliens; ++i)
    {
        Alien_Gold alien(surface, true);
        if (i == 0)
        {
            alien.x((width / 2) + alien.w() + 10);
            alien.y(90);
        }
        else if (i < 3)
        {
            alien.x(fleet_gold[i - 1].x() + fleet_gold[i - 1].w() + 40 + (alien.w() * 3));
            alien.y(fleet_gold[0].y());
        }
        fleet_gold.push_back(alien);
    }
    fleet_gold.shrink_to_fit();
}


void build_purple(Surface & surface, std::vector < Alien_Purple > & fleet_purple,
                  int width)
{
    int max_aliens = 6;
    
    for (int i = 0; i < max_aliens; ++i)
    {
        Alien_Purple alien(surface, true);
        if (i == 0)
        {
            alien.x(width / 2);
            alien.y(150);
        }
        else if (i < 6)
        {
            alien.x(fleet_purple[i - 1].x() + fleet_purple[i - 1].w() + 20 + alien.w());
            alien.y(fleet_purple[0].y());
        }
        
        fleet_purple.push_back(alien);
    }
    fleet_purple.shrink_to_fit();
}

    
