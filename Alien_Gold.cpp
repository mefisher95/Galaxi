#include "Alien_Gold.h"

int Alien_Gold::num_aliens(0);
int Alien_Gold::points_(100);
Image Alien_Gold::image_("images/galaxian/GalaxianFlagship.gif");
/*
void Alien_Gold::build()
{
    std::cout << "im here" <<  std::endl;
    rect_.y = 100;
    rect_.x = W / 2 - (rect_.w / 2);
}
*/
void Alien_Gold::draw()
{
    if (alive_)
    surface_.put_image(image_, rect_);
}

void Alien_Gold::move(int direction)
{
    rect_.x += direction;
}

void Alien_Gold::alive(bool alive)
{
    alive_ = alive;
}

bool Alien_Gold::alive() const
{
    return alive_;
}

void Alien_Gold::x(int x)
{
    //std::cout << "setting gold x: " << x << std::endl;
    rect_.x = x;
}

int Alien_Gold::x() const
{
    return rect_.x;
}

void Alien_Gold::y(int y)
{
    rect_.y = y;
}

int Alien_Gold::y() const
{
    return rect_.y;
}

void Alien_Gold::h(int h)
{
    rect_.h = h;
}

int Alien_Gold::h() const
{
    return rect_.h;
}

void Alien_Gold::w(int w)
{
    rect_.w = w;
}

int Alien_Gold::w() const
{
    return rect_.w;
}

int Alien_Gold::gun_x() const
{
    return ((rect_.x + (rect_.x + rect_.w)) / 2);
}

int Alien_Gold::gun_y() const
{
    return rect_.y;
}
