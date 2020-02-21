#include "Alien_Purple.h"

int Alien_Purple::num_aliens(0);
int Alien_Purple::points_(75);
Image Alien_Purple::image_("images/galaxian/GalaxianPurpleAlien.gif");

void Alien_Purple::build()
{
    rect_.y = 100;
    rect_.x = W / 2 - (rect_.w / 2);
}

void Alien_Purple::draw()
{
    if (alive_)
    surface_.put_image(image_, rect_);
}

void Alien_Purple::move(int direction)
{
    rect_.x += direction;
}

void Alien_Purple::alive(bool alive)
{
    alive_ = alive;
}

bool Alien_Purple::alive() const
{
    return alive_;
}

void Alien_Purple::x(int x)
{
    rect_.x = x;
}

int Alien_Purple::x() const
{
    return rect_.x;
    //return 400;
}

void Alien_Purple::y(int y)
{
    rect_.y = y;
}

int Alien_Purple::y() const
{
    return rect_.y;
}

void Alien_Purple::h(int h)
{
    rect_.h = h;
}

int Alien_Purple::h() const
{
    return rect_.h;
}

void Alien_Purple::w(int w)
{
    rect_.w = w;
}

int Alien_Purple::w() const
{
    return rect_.w;
}

int Alien_Purple::gun_x() const
{
    return ((rect_.x + (rect_.x + rect_.w)) / 2);
}

int Alien_Purple::gun_y() const
{
    return rect_.y;
}
