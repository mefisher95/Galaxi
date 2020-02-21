#include "Fleet_Fire.h"


void fire_blue(std::vector < Laser > &, std::vector < Alien_Blue > &);
void fire_purple(std::vector < Laser > &, std::vector < Alien_Purple > &);


void fleet_fire(std::vector < Laser > & laser_array,
                std::vector < Alien_Blue > & fleet_blue,
                std::vector < Alien_Red > & fleet_red,
                std::vector < Alien_Gold > & fleet_gold,
                std::vector < Alien_Purple > & fleet_purple,
                int & delay_)
{
    int option = rand() % 2;
    switch (option)
    {
        case 1:
            fire_purple(laser_array, fleet_purple);
            delay_ = 0;
            break;
        case 0:
             fire_blue(laser_array, fleet_blue);
             delay_ = 0;
             break;
    }
}

void fire_blue(std::vector < Laser > & laser_array,
               std::vector < Alien_Blue > & fleet)
{
    int fire = 0;
    for (int i = 0; i < fleet.size(); ++i)
    {
        if (fleet[i].alive())
        {
            fire = i;
            break;
        }
    }
    
    while(!fleet[fire].alive())
    {
        fire = rand() % 23;
        if (fleet[fire].get_num() == 0) break;
    }
    
    if (fleet[fire].alive())
    {
        for (int i = 0; i < 100; ++i)
        {
            if (!laser_array[i].alive())
            {
               
                laser_array[i].player(false);
                laser_array[i].build(fleet[fire].gun_x(), fleet[fire].gun_y());
                laser_array[i].alive(true);
                
                return;
            }
        }
    }
}


void fire_purple(std::vector < Laser > & laser_array,
                 std::vector < Alien_Purple > & fleet)
{
    for (int j = 0; j < 6; ++j)
    {
        if (fleet[j].alive())
        {
            for (int i = 0 ; i < 100; ++i)
            {
                if (!laser_array[i].alive())
                {
                    laser_array[i].player(false);
                    laser_array[i].build(fleet[j].gun_x(), fleet[j].gun_y());
                    laser_array[i].alive(true);
                    
                    break;
                }
            }
        }
    }
}
