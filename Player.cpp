#include "Player.h"

Image Player::image_("images/galaxian/GalaxianGalaxip.gif");

void Player::draw()
{
    surface_.put_image(image_, rect_); // draw player ship    
}

void Player::build()
{
    //set default starting positon
    rect_.y = H - 150; //y pos
    rect_.x = W / 2 - (rect_.w / 2); // x pos
}

void Player::move()
{
    KeyPressed keypress = get_keypressed();

    //player movement speed
    speed_ = 5;

    //movement keys 8-deg of motion
    
    if ((keypress[LEFTARROW] || keypress[a]) &&
        (keypress[UPARROW] || keypress[w]))
    {
        left_x();
        up_y();
    }
    else if ((keypress[RIGHTARROW] || keypress[d]) &&
             (keypress[UPARROW] || keypress[w]))
    {
        right_x();
        up_y();
    }
    else if ((keypress[LEFTARROW] || keypress[a]) &&
             (keypress[DOWNARROW]|| keypress[s]))
    {
        left_x();
        down_y();
    }
    else if ((keypress[RIGHTARROW] || keypress[d]) &&
             (keypress[DOWNARROW] || keypress[s]))
    {
        right_x();
        down_y();
    }
    else if (keypress[LEFTARROW] || keypress[a])
    {
        left_x();
    }
    else if (keypress[RIGHTARROW] || keypress[d])
    {
        right_x();
    }
    else if (keypress[UPARROW] || keypress[w])
    {
        up_y();
    }
    else if (keypress[DOWNARROW] || keypress[s])
    {
        down_y();
    }
    
}


//move functions for use in movement keys
void Player::down_y()
{
    if (rect_.y + rect_.h >= H - 50) rect_.y = H - rect_.h - 50;
    else rect_.y += speed_;
}

void Player::up_y()
{
    if (rect_.y <= H / 2) rect_.y = H / 2;
    else rect_.y -= speed_;
}

void Player::left_x()
{
    if (rect_.x <= 1) rect_.x = 1;
    else rect_.x -= speed_;
}

void Player::right_x()
{
    if (rect_.x + rect_.w >= W - 10) rect_.x = W - rect_.w - 10;
    rect_.x += speed_;
}


// returns position of ship gun for firing lasers
int Player::get_gun_x() const
{
    return ((rect_.x + (rect_.x + rect_.w)) / 2);
}

int Player::get_gun_y() const
{
    return rect_.y - 10;
}


// returns number of lives of player
int Player::lives() const
{
    return lives_;
}

void Player::lives(int lives)
{
    lives_ = lives;
}
