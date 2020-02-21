#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Rect.h"

#include "HUD.h"
#include "Highscores.h"
#include "Stars.h"
#include "Player.h"
#include "Laser.h"
#include "mainFunctions.h"
#include "Fleet_Build.h"
#include "Fleet_Draw.h"
#include "Fleet_Move.h"
#include "Fleet_Collide.h"
#include "Fleet_Fire.h"
#include "Explosion.h"

//==============================================================================
// Galaxian
// main.cpp
// Michael Fisher
//==============================================================================
// This file contains the primary functions of the Galaxian Project for CISS245.
// Combining the use of two primary functions (main() and play()), the program
// will execute a series of function calls in main before executing the primary
// gameplay loop in play(). The user will have the ability to terminate the
// gameplay loop at anytime and can reinitilize it from main() again.
//==============================================================================

void Play(Surface &, Event &, KeyPressed &, Galaxy &, bool &, std::vector < int > &);
void Drop(std::vector < Alien_Blue > &, std::vector < Alien_Red > &,
          std::vector < Alien_Gold > &, std::vector < Alien_Purple > &,
          bool &, int);
    
int main(int argc, char* argv[])
{
    //========================================================================//
    // CREATE UNIVERSE
    //========================================================================//
    KeyPressed keypress;
    Event event;
    Music game_music("sounds/CallMeMaybe.wav");
    Surface surface(W, H);
    Galaxy galaxy(surface);
    galaxy.build();
    game_music.play();
    std::vector < int > highscore;
    for (int i = 0; i < 10; ++i)
    {
        highscore.push_back(0);
    }
    highscore.shrink_to_fit();

    //========================================================================//
    // LAUNCH GAME
    //========================================================================//
    while(1)
    {
        bool play = false;
        bool rules = false;
        bool score = false;
        bool exit = false;

        read(highscore);
        
        // launch main menu
        if (!exit) main_menu(surface, event, galaxy, keypress, play, rules,
                             score, exit, highscore);
        // launch play loop
        if (play) Play(surface, event, keypress, galaxy, exit, highscore);

        // launch Rules screen
        if (rules) game_rules(surface, keypress, event, galaxy, rules, exit);

        // launch highscore menu
        if (score) high_score(surface, keypress, event, galaxy, exit, highscore);
        
        // terminate program
        if (exit) break;
    }
    
    return 0;
}



void Play(Surface & surface, Event & event, KeyPressed & keypress,
          Galaxy & galaxy, bool & exit, std::vector < int > & highscore)
{
    //========== create all objects ==========//                     
    Player player(surface);                    // playable character
    std::vector < Laser > laser_array;         // vector of 200 laser objects
    std::vector < Explosion > explosion;       // create a vector of explosions:)
    
    // Fleet vectors
    std::vector < Alien_Blue > fleet_blue;     // 22 blue  aliens
    std::vector < Alien_Red > fleet_red;       // 9  red   aliens
    std::vector < Alien_Gold > fleet_gold;     // 3  gold  aliens
    std::vector < Alien_Purple > fleet_purple; // 5  puple aliens
    
    //========== create HUD ===========//
    Font font("fonts/space_age.ttf", 40);
    char Str_score[16];
    int score;
    Image left(font.render("LIVES:", YELLOW));
    Image center(font.render("SCORE :", YELLOW));

    Image top(font.render("FLEETS: ", YELLOW));
    char Str_fleet[3];
    int Fleet = 1;
    Rect fleet_fleettext = top.getRect();
    fleet_fleettext.x = 0;
    fleet_fleettext.y = 0;
    Rect fleet_num;
    
    
    //========== build objects ==========//
    player.build();

    build_explosion(surface, explosion);

    build_laser_array(surface, laser_array);    

    fleet_build(surface, fleet_blue, fleet_red, fleet_gold, fleet_purple);
    
    //========== delay counters ==========//
    int endgame_count = 0;   // executes end_game() when count = 100
    int death_count = 0;
    bool trigger = 0;        // trigger for firing lasers
    bool kill_trigger = 0;   // trigger for debug lives decrement
    bool save_trigger = 0;   // trigger for debug lives increment

    int alien_direction = 5;
    int alien_attack_delay_ = 0;
    int player_attack_delay = 0;
    int alien_count;
    int option;

    bool drop = false;
    
    HUD::score_ = 0;
    
    while(1)
    {
        score = HUD::score_;
        sprintf(Str_score, "%d", score);
        Image right(font.render(Str_score, CYAN));
        HUD hud(surface, left, center, right, player.lives());

        sprintf(Str_fleet, "%d", Fleet);
        Image fleet_num_image(font.render(Str_fleet, CYAN));
        fleet_num = fleet_num_image.getRect();
        fleet_num.x = fleet_fleettext.x + fleet_fleettext.w + 20;
        
        alien_count = fleet_blue[0].get_num() + fleet_red[0].get_num()
            + fleet_gold[0].get_num() + fleet_purple[0].get_num();
        
        if (alien_count == 0) ++Fleet;
        
        //====================================================================//
        // USER INPUTS                                                        //
        //====================================================================//
        
        keypress = get_keypressed();

        //========== exit strategy ==========//
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }
        if (keypress[ESC])
        {
            //hud.update_score();
            write(highscore);
            alien_count = 0;
            return;
        }

        //========== debug commands ==========//
        // kill key for debugging
        /*
        if (keypress[TAB] && event.type() == KEYDOWN)
        {
            kill_trigger = true;
        }
        if (event.type() == KEYUP && kill_trigger)
        {
            if (player.lives() > 0) player.lives(player.lives() - 1);  
            kill_trigger = false;
            
            std::cout << "alien gold: " << std::endl;
            for (int i = 0; i < 3; ++i)
            {
                std::cout << "i: " << i
                          << " y: " << fleet_gold[i].y()
                          << " x: " << fleet_gold[i].x()
                          << " a: " << fleet_gold[i].alive()
                          << std::endl;
            }
            std::cout << "alien red: " << std::endl;
            for (int i = 0; i < 9; ++i)
            {
                std::cout << "i: " << i
                          << " y: " << fleet_red[i].y()
                          << " x: " << fleet_red[i].x()
                          << " a: " << fleet_red[i].alive()
                          << std::endl;
            }
            std::cout << "alien purple: " << std::endl;
            for (int i = 0; i < 6; ++i)
            {
                std::cout << "i: " << i
                          << " y: " << fleet_purple[i].y()
                          << " x: " << fleet_purple[i].x()
                          << " a: " << fleet_purple[i].alive()
                          << std::endl;
            }
            std::cout << "alien blue: " << std::endl;
            for (int i = 0; i < 22; ++i)
            {
                std::cout << "i: " << i
                          << " y: " << fleet_blue[i].y()
                          << " x: " << fleet_blue[i].x()
                          << " a: " << fleet_blue[i].alive()
                          << std::endl;
            }
            std::cout << "alien count: " << alien_count << std::endl;
        }
        // lives up for debugging
        if (keypress[BACKQUOTE] && event.type() == KEYDOWN)
        {
            save_trigger = true;
        }
        if (event.type() == KEYUP && save_trigger)
        {
            if (player.lives() < 3) player.lives(player.lives() + 1);  
            save_trigger = false;
        }
        */
        if (keypress[F] && event.type() == KEYDOWN)
            fire(laser_array, keypress, player);
        
        //========== firing ==========//
        //player laser firing
        if ((keypress[SPACE] || keypress[ENTER]) && event.type() == KEYDOWN &&
            player_attack_delay == 0)
        {
            fire(laser_array, keypress, player);
            ++player_attack_delay;
        }
        if (player_attack_delay > 0 && player_attack_delay < 10)
        {
            ++player_attack_delay;
        }
        else player_attack_delay = 0;
       
        
        //====================================================================//
        // EXECUTE MOVE COMMANDS
        //====================================================================//

   
        for (int i = 0; i < 100; ++i)
        {
            if (i < explosion.size())
            {
                explosion[i].disperse();
                explosion[i].fall();
            }
            //========== alien respawn and reposition ==========//
            
            //respawn
            if (alien_count <= 0)
                rebirth(fleet_blue, fleet_red, fleet_gold, fleet_purple, i);                
            

            // drop down from off screen
            reposition(fleet_blue, fleet_red, fleet_gold, fleet_purple, i);
            
            //========== detect collisons ==========//
            // player detection
            if ((collision(laser_array, player, explosion, i) ||
                 collision(fleet_gold, player, i) ||
                 collision(fleet_red, player, i) ||
                 collision(fleet_blue, player, i))
                && (player.lives() > 0)
                && death_count == 0)
            {
                find_explosion(explosion, player.get_x(), player.get_y());
                player.lives(player.lives() - 1);
                ++death_count;
            }            
            // enemy detection
            fleet_collide(laser_array, fleet_blue, fleet_red, fleet_gold,
                          fleet_purple, explosion, player, i);            
        
           
            //===codegoeshere===//
            
            // lasers move
            laser_array_move(laser_array, i);
        }
        // increment delay between alien attacks outside of loop
        ++alien_attack_delay_;

         //========== move ships ==========//
        
         // move enemy
         fleet_move(alien_direction, fleet_blue, fleet_red, fleet_gold,
                    fleet_purple);
         // move player
         player.move();

         if (drop == false && alien_count == 20)
         {
             drop = true;
             option = 1;
         }
         if (drop == false && fleet_gold[0].get_num() == 0)
         {
             drop = true;
             option = 2;
         }
         else if (option == 2 && fleet_gold[0].get_num() != 0)
         {
             drop = false;
         }
         if (drop == false && rand() % 1000 == 1)
         {
             drop = true;
             option = 3;
         }
         //========== attack actions ===========//
         // enemy fires
         if (alien_attack_delay_ == 50)
             fleet_fire(laser_array, fleet_blue, fleet_red, fleet_gold, fleet_purple,
                        alien_attack_delay_);
         // enemy drops

         Drop(fleet_blue, fleet_red, fleet_gold, fleet_purple, drop, option);

        //====================================================================//
        // EXECUTE DRAW COMMANDS
        //====================================================================//
        surface.lock();

        surface.fill(BLACK);

        galaxy.draw();  
        for (int i = 0; i < 100; ++i)
        {     
            laser_array_draw(laser_array, i);
            if (i < 30) explosion[i].draw();
            fleet_draw(surface, fleet_blue, fleet_red, fleet_gold,
                       fleet_purple, i);
        }
        
        hud.draw(player.lives());
        if (death_count == 0) player.draw();       
        surface.put_image(top, fleet_fleettext);
        surface.put_image(fleet_num_image, fleet_num);
        surface.unlock();
        surface.flip();
        delay(GAMESPEED);
        
        //====================================================================//
        // EXECUTE END GAME
        //====================================================================//

        // temperary immunity after being shot
        if(death_count < 10 && death_count > 0) ++death_count;
        else if (death_count == 10) death_count = 0;
       
        // ends game
        if(player.lives() == 0)
        {
            ++endgame_count;
            if (endgame_count == 60)
            {
                end_game(surface, keypress, event, exit);
                //hud.update_score();
                write(highscore);
                alien_count = 0;
                return;
            }
        }
        else endgame_count = 0;
    }

    return;
}


void Drop(std::vector < Alien_Blue > & blue, std::vector < Alien_Red > & red,
          std::vector < Alien_Gold > & gold, std::vector < Alien_Purple > & purple,
          bool & drop, int option)
{
    if (drop == true && option == 1)
    {
        for (int i = 0; i < 9; ++i)
        {
            if (gold[0].y() < H - 51)
            {
                if (i < 3) gold[i].y(gold[i].y() + 5);
                red[i].y(red[i].y() + 5);
            }
            else if (gold[0].y() >= H - 51)
            {
                gold[0].y(-210);
                gold[1].y(-210);
                gold[2].y(-210);
                red[0].y(-175);
                red[1].y(-175);
                red[2].y(-175);

                red[3].y(-210);
                red[4].y(-210);
                red[5].y(-210);
                red[6].y(-210);
                red[7].y(-210);
                red[8].y(-210);
                
                drop = false;
            }
        }
    }

    if (drop == true && option == 2)
    {
        for (int i = 0; i < 9; ++i)
        {
            if (red[3].y() < H - 51)
            {
                red[i].y(red[i].y() + 5);
            }
            else
            {
                red[0].y(-175);
                red[1].y(-175);
                red[2].y(-175);

                red[3].y(-210);
                red[4].y(-210);
                red[5].y(-210);
                red[6].y(-210);
                red[7].y(-210);
                red[8].y(-210);
            }
        }
    }

    if (drop == true && option == 3)
    {
        for (int i = 0; i < 22; ++i)
        {
            if (blue[0].y() <= H - 51)
            {
                blue[i].y(blue[i].y() + 5);
            }
            else
            {
                blue[0].y(-100);
                blue[1].y(-100);
                blue[2].y(-100);
                blue[3].y(-100);
                blue[4].y(-100);
                blue[5].y(-100);
                blue[6].y(-100);
                blue[7].y(-100);
                blue[8].y(-100);
                blue[9].y(-100);
                blue[10].y(-100);
            
                blue[11].y(-58);
                blue[12].y(-58);
                blue[13].y(-58);
                blue[14].y(-58);
                blue[15].y(-58);
                blue[16].y(-58);
                blue[17].y(-58);
                blue[18].y(-58);
                blue[19].y(-58);
                blue[20].y(-58);
                blue[21].y(-58);
                
                drop = false;
            }
        }
    }
}
 
