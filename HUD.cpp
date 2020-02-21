#include "HUD.h"
#include "Includes.h"

Image HUD::ships_("images/galaxian/GalaxianGalaxip.gif");
int HUD::score_ = 0;
//int HUD::highScore_ = 0;

void HUD::draw(const int & lives)
{
    // put HUD line
    surface_.put_rect(0, H - 50, W, 50, 0, 0, 0);
    surface_.put_rect(0, H - 50, W, 3, 0, 255, 255);

    // put lives text
    left_rect_.x = 0;
    left_rect_.y = H - 50;

    right_rect_.x = W - right_rect_.w;
    right_rect_.y = left_rect_.y;

    center_rect_.x = right_rect_.x - center_rect_.w;
    center_rect_.y = left_rect_.y;

    surface_.put_image(left_, left_rect_);
    surface_.put_image(center_, center_rect_);
    surface_.put_image(right_, right_rect_);

    lives_ = lives;
    surface_.put_rect(ships_rect_, BLACK);

    // put lives
    if (lives_ >= 1)
    {
        ships_rect_.x = left_rect_.w + 5;
        ships_rect_.y = H - 45;
        surface_.put_image(ships_, ships_rect_);
    }
    if (lives_ >= 2)
    {
        ships_rect_.x = left_rect_.w + ships_rect_.w + 10;
        ships_rect_.y = H - 45;
        surface_.put_image(ships_, ships_rect_);        
    }
    if (lives_ == 3)
    {
        ships_rect_.x = left_rect_.w + ships_rect_.w + ships_rect_.w + 15;
        ships_rect_.y = H - 45;
        surface_.put_image(ships_, ships_rect_);
    }
}

/*
void HUD::update_score()
{
    if (score_ >= highscores_[0])
        highscores_[0] = score_;
}
*/
