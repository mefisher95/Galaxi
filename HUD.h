#ifndef HUD_H
#define HUD_H

#include <vector>
#include "Includes.h"
#include "Constants.h"

class HUD
{
public:
HUD(Surface & surface, Image & left, Image & center, Image & right, int lives)
    :surface_(surface), left_(left), center_(center), right_(right), lives_(lives)
    {
        left_rect_ = left_.getRect();
        center_rect_ = center_.getRect();
        right_rect_ = right_.getRect();
        ships_rect_ = ships_.getRect();
    }

    void draw(const int & live);
    //void update_score();
    int score() const {return score_;}
    void score(int score) {score_ = score;}

    void inc_score(int points) {score_ += points;}
    
    //int highScore() const {return highScore_;}
    //void highScore(int highScore) {highScore_ = highScore;}

    static int score_;
private:
    
    static Image ships_;
    Surface & surface_;
    Rect left_rect_;
    Rect center_rect_;
    Rect right_rect_;
    Rect background_rect_;
    Rect ships_rect_;
    int lives_;
    Image & left_;
    Image & center_;
    Image & right_;    
};


#endif
