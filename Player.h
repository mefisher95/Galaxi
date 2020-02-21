#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Includes.h"
#include "Constants.h"
#include "Laser.h"

class Player
{
public:
Player(Surface & surface, int speed = 2, int lives = 3)
    :surface_(surface), speed_(speed), lives_(lives)
    {
        rect_ = image_.getRect();
    }

    void draw();
    void build();
    void move();
    
    void down_y();
    void up_y();
    void left_x();
    void right_x();

    int get_x() const
    {
        return rect_.x;
    }
    int get_y() const
    {
        return rect_.y;
    }
    int get_w() const
    {
        return rect_.w;
    }
    int get_h() const
    {
        return rect_.h;
    }

    int get_gun_x() const;
    int get_gun_y() const;

    void lives(int lives);
    int lives() const;
    static int score;
private:
    static Image image_;
    
    Surface & surface_;
    Rect rect_;
    int speed_;
    int lives_;
};

void fire();

#endif
