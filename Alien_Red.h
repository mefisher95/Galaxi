#ifndef ALIEN_RED_H
#define ALIEN_RED_H

#include "Includes.h"
#include "Constants.h"
#include "Alien_Blue.h"

class Alien_Red
{
public:
Alien_Red(Surface & surface, bool alive)
    :surface_(surface), alive_(alive)
    {
        rect_ = image_.getRect();
    }

    void draw();
    void build();
    void move(int direction);

    void alive(bool);
    bool alive() const;
    
    int gun_x() const;
    int gun_y() const;
    
    void x(int x);
    int x() const;
    void y(int y);
    int y() const;
    void h(int h);
    int h() const;
    void w(int w);
    int w() const;

    int get_num() const { return num_aliens; }
    void set_num(int num) { num_aliens = num; }
    void inc_num() { ++num_aliens; }
    void dec_num() { --num_aliens; }

    
    static int points_;
private:
    static Image image_;
    static int num_aliens;
    
    Surface & surface_;
    bool alive_;
    Rect rect_;
};

#endif
