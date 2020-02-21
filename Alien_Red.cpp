#include "Alien_Red.h"

int Alien_Red::num_aliens(0);
int Alien_Red::points_(50);
Image Alien_Red::image_("images/galaxian/GalaxianRedAlien.gif");

void Alien_Red::build()
{
    rect_.y = 100;
    rect_.x = W / 2 - (rect_.w / 2);
}

void Alien_Red::draw()
{
    if (alive_)
    surface_.put_image(image_, rect_);
}

void Alien_Red::move(int direction)
{
    rect_.x += direction;
}

void Alien_Red::alive(bool alive)
{
    alive_ = alive;
}

bool Alien_Red::alive() const
{
    return alive_;
}

void Alien_Red::x(int x)
{
    rect_.x = x;
}

int Alien_Red::x() const
{
    return rect_.x;
    //return 200;
}

void Alien_Red::y(int y)
{
    rect_.y = y;
}

int Alien_Red::y() const
{
    return rect_.y;
}

void Alien_Red::h(int h)
{
    rect_.h = h;
}

int Alien_Red::h() const
{
    return rect_.h;
}

void Alien_Red::w(int w)
{
    rect_.w = w;
}

int Alien_Red::w() const
{
    return rect_.w;
}

int Alien_Red::gun_x() const
{
    return ((rect_.x + (rect_.x + rect_.w)) / 2);
}

int Alien_Red::gun_y() const
{
    return rect_.y;
}
