#include <iostream>
#include "Stars.h"
#include "Surface.h"

void Galaxy::draw()
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (stars[i].y() >= H - 51)
        {
            stars[i].y(0);
            stars[i].x(rand() % W);
        }
        stars[i].move();
        surface_.put_rect(stars[i].x(), stars[i].y(), stars[i].w(), stars[i].h(),
                          stars[i].r(), stars[i].g(), stars[i].b());
    }
}

void Galaxy::build()
{
    for (int i = 0; i < SIZE; ++i)
    {
        Stars star;
        
        star.x(rand() % W);
        star.y(rand() % (H - 51));

        star.type(rand() % 3 + 1);
        
        if (star.type() == 1)
        {
            star.w(1);
            star.h(1);
            star.speed(1);
            star.r(150);
            star.g(150);
            star.b(150);
        }
        else if (star.type() == 2)
        {
            star.w(2);
            star.h(2);
            star.speed(2);
            star.r(175);
            star.g(175);
            star.b(175);
        }
        else if (star.type() == 3)
        {
            star.w(2);
            star.h(2);
            star.speed(4);
            star.r(180);
            star.g(180);
            star.b(255);
        }
        stars.push_back(star);
    }
    stars.shrink_to_fit();
}

void Stars::move()
{
    y_ += speed_;
}
