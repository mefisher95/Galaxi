#include "Alien_Blue.h"

int Alien_Blue::num_aliens(0);
int Alien_Blue::points_(20);

Image Alien_Blue::image_("images/galaxian/GalaxianAquaAlien.gif");

void Alien_Blue::build()
{
    rect_.y = 100;
    rect_.x = W / 2 - (rect_.w / 2);
}

void Alien_Blue::draw()
{
    if (alive_)
    surface_.put_image(image_, rect_);
}

void Alien_Blue::move(int direction)
{
    rect_.x += direction;
}

void Alien_Blue::alive(bool alive)
{
    alive_ = alive;
}

bool Alien_Blue::alive() const
{
    return alive_;
}

void Alien_Blue::x(int x)
{
    rect_.x = x;
}

int Alien_Blue::x() const
{
    return rect_.x;
    //return 300;
}

void Alien_Blue::y(int y)
{
    rect_.y = y;
}

int Alien_Blue::y() const
{
    return rect_.y;
}

void Alien_Blue::h(int h)
{
    rect_.h = h;
}

int Alien_Blue::h() const
{
    return rect_.h;
}

void Alien_Blue::w(int w)
{
    rect_.w = w;
}

int Alien_Blue::w() const
{
    return rect_.w;
}

int Alien_Blue::gun_x() const
{
    return ((rect_.x + (rect_.x + rect_.w)) / 2);
}

int Alien_Blue::gun_y() const
{
    return rect_.y;
}
