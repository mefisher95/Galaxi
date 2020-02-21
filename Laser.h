#ifndef LASER_H
#define LASER_H

#include "Includes.h"
#include "Player.h"

class Laser
{
public:
Laser(Surface & surface, int x = 0, int y = 0, int h = 10, int w = 1,
      bool alive = false, bool player = false, int r = 250, int g = 150, int b = 0)
    :surface_(surface), x_(x), y_(y), h_(h), w_(h), r_(r), g_(g), b_(b),
        alive_(alive), player_(player)
    {}

    void draw();
    void move();
    void build(int x, int y);
    
    void alive(bool alive)
    {
        alive_ = alive;
    }
    bool alive() const
    {
        return alive_;
    }
    void player(bool player)
    {
        player_ = player;
    }
    bool player() const
    {
        return player_;
    }

    int x() const
    {
        return x_;
    }
    int y() const
    {
        return y_;
    }
    
    
private:
    Surface & surface_;
    int x_, y_, h_, w_;
    int r_, g_, b_;
    bool alive_;
    bool player_;

    static Sound sound;
};



#endif

