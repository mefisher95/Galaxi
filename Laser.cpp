#include <vector>
#include "Laser.h"
#include "Player.h"

Sound Laser::sound("sounds/laser.wav");

void Laser::draw()
{
    if (alive_)
    {
        surface_.put_rect(x_, y_, w_, h_, r_, g_, b_);
    }
}

void Laser::move()
{
    int direction;
    if (player_) direction = 10;
    if (!player_) direction = -10;
    
    if (alive_)
    {
        surface_.put_rect(x_, y_, w_, h_, 0, 0, 0);
        if (y_ > 0 && y_ <= H - h_ - 51)
        {
            y_ -= direction;
        }
        else
        {
            alive_ = false;
        }
    }
}

void Laser::build(int x, int y)
{
    if (!alive_)
    {
        alive_ = true;
        x_ = x;
        y_ = y;
        w_ = 2;
        h_ = 20;

        sound.play();
        if (player_)
        {
            r_ = 250;
            g_ = 150;
            b_ = 0;
        }
        else if (!player_)
        {
            r_ = 0;
            g_ = 250;
            b_ = 150;
        }
    }
}
