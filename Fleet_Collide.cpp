#include "Fleet_Collide.h"


void collide_blue(std::vector < Laser > &, std::vector < Alien_Blue > &,
                  std::vector < Explosion > &, int, int);
void collide_red(std::vector < Laser > &, std::vector < Alien_Red > &,
                 std::vector < Explosion > &, int, int);
void collide_gold(std::vector < Laser > &, std::vector < Alien_Gold > &,
                  std::vector < Explosion > &, Player & player, int, int);
void collide_purple(std::vector < Laser > &, std::vector < Alien_Purple > &,
                    std::vector < Explosion > &, int, int);


void fleet_collide(std::vector < Laser > & laser_array,
                   std::vector < Alien_Blue > & fleet_blue,
                   std::vector < Alien_Red > & fleet_red,
                   std::vector < Alien_Gold > & fleet_gold,
                   std::vector < Alien_Purple > & fleet_purple,
                   std::vector < Explosion > & explosion,
                   Player & player,
                   int i)
{
    for (int j = 0; j < fleet_blue.size(); ++j)
    {
        collide_blue(laser_array, fleet_blue, explosion, i, j);
        if (j < fleet_red.size()) collide_red(laser_array, fleet_red, explosion, i, j);
        if (j < 3) collide_gold(laser_array, fleet_gold, explosion, player, i, j);
        if (j < 6) collide_purple(laser_array, fleet_purple, explosion, i, j);
    }
}

void collide_blue(std::vector < Laser > & laser_array,
                  std::vector < Alien_Blue > & fleet,
                  std::vector < Explosion > & explosion,
                  int i, int j)
{
    if ((laser_array[i].x() >= fleet[j].x() &&
         laser_array[i].x() <= fleet[j].x() + fleet[j].w()) &&
        (laser_array[i].y() >= fleet[j].y() &&
         laser_array[i].y() <= fleet[j].y() + fleet[j].h()) &&
        (fleet[j].alive() && laser_array[i].alive() && laser_array[i].player()))
    {
        fleet[j].alive(false);
        laser_array[i].alive(false);
        HUD::score_ += Alien_Blue::points_;
        fleet[j].dec_num();
        find_explosion(explosion, fleet[j].x(), fleet[j].y());
    }
}

void collide_red(std::vector < Laser > & laser_array,
                 std::vector < Alien_Red > & fleet,
                 std::vector < Explosion > & explosion,
                 int i, int j)
{
    if ((laser_array[i].x() >= fleet[j].x() &&
         laser_array[i].x() <= fleet[j].x() + fleet[j].w()) &&
        (laser_array[i].y() >= fleet[j].y() &&
         laser_array[i].y() <= fleet[j].y() + fleet[j].h()) &&
        (fleet[j].alive() && laser_array[i].alive() && laser_array[i].player()))
    {
        fleet[j].alive(false);
        laser_array[i].alive(false);
        HUD::score_ += Alien_Red::points_;
        fleet[j].dec_num();
        find_explosion(explosion, fleet[j].x(), fleet[j].y());
    }
}


void collide_gold(std::vector < Laser > & laser_array,
                  std::vector < Alien_Gold > & fleet,
                  std::vector < Explosion > & explosion,
                  Player & player,
                  int i, int j)
{
    if ((laser_array[i].x() >= fleet[j].x() &&
         laser_array[i].x() <= fleet[j].x() + fleet[j].w()) &&
        (laser_array[i].y() >= fleet[j].y() &&
         laser_array[i].y() <= fleet[j].y() + fleet[j].h()) &&
        (fleet[j].alive() && laser_array[i].alive() && laser_array[i].player()))
    {
        fleet[j].alive(false);
        laser_array[i].alive(false);
        fleet[j].dec_num();
        find_explosion(explosion, fleet[j].x(), fleet[j].y());

        HUD::score_ += Alien_Gold::points_;
        int rando = rand() % 10;
        if (player.lives() < 3 && rando == 3) player.lives(player.lives() + 1);
    }
}

void collide_purple(std::vector < Laser > & laser_array,
                    std::vector < Alien_Purple > & fleet,
                    std::vector < Explosion > & explosion,
                    int i, int j)
{
    if ((laser_array[i].x() >= fleet[j].x() &&
         laser_array[i].x() <= fleet[j].x() + fleet[j].w()) &&
        (laser_array[i].y() >= fleet[j].y() &&
         laser_array[i].y() <= fleet[j].y() + fleet[j].h()) &&
        (fleet[j].alive() && laser_array[i].alive() && laser_array[i].player()))
    {
        fleet[j].alive(false);
        laser_array[i].alive(false);
        HUD::score_ += Alien_Purple::points_;
        fleet[j].dec_num();
        find_explosion(explosion, fleet[j].x(), fleet[j].y());
    }
}
