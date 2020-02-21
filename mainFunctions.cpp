#include "mainFunctions.h"
#include <string>


//==============================================================================
// mainFunction.cpp
// Michael Fisher
//==============================================================================
// This file contains all of the main nonmember funcitons of Galaxian. This list
// includes:
// - main_menu()
// - end_game()
// - build_laser_array()
// - fire()
// - laser_array_move()
// - laser_array_draw()
//==============================================================================


/*******************************************************************************
 --main_menu()--

 main boot menu for the program.
*******************************************************************************/
void main_menu(Surface & surface, Event & event, Galaxy & galaxy,
               KeyPressed & keypress, bool & play, bool & rules, bool & score,
               bool & exit, std::vector < int > & highscores)
{
    char Str_highscore[16];

    int highscore = highscores[0];

    sprintf(Str_highscore, "%d", highscore);

    //creator text;
    Font creator_font("fonts/space_age.ttf", 30);
    Image creator_text(creator_font.render("Michael Fisher, 2019",
                                           0, 255, 255));
    Image center_text(creator_font.render("HIGHSCORE: ", YELLOW));
    Image highscore_text(creator_font.render(Str_highscore, CYAN));
    Image player_ship("images/galaxian/GalaxianGalaxip.gif");
    Rect player_rect = player_ship.getRect();
    
    HUD creator(surface, creator_text, center_text, highscore_text, 0);

    int r = 0, g = 0, b = 0;
    // create GALAXIAN title card
    Font font_title("fonts/space_age.ttf", 100);

    bool trigger = false;     //trigger for KEYUP/DOWN event
    
    // opening fade
    for (int i = 0; i < 250; ++i)
    {
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }
        
        keypress = get_keypressed();
        if ((keypress[SPACE] || keypress[ENTER]) && event.type() == KEYDOWN)
        {
            trigger = true;
        }

        if (event.type() == KEYUP && trigger)
        {
            r = 250;
            trigger = false;
            break;
        }
        
        ++r; // fade in the red color of the title card
        
        Image title(font_title.render("GALAXI", r, g, b));
        Rect rect_title = title.getRect();
        rect_title.y = H / 2 - (rect_title.h / 2) - 100; //y pos
        rect_title.x = W / 2 - (rect_title.w / 2); // x pos

        surface.lock();
        
        surface.fill(BLACK);
       
        galaxy.draw();
        
        surface.put_image(title, rect_title);
        creator.draw(0);
        
        surface.unlock();
        surface.flip();
        
        delay(GAMESPEED);
    }

    //create objects for menu options
    Image title(font_title.render("GALAXI", RED));
    Rect rect_title = title.getRect();
    rect_title.y = H / 2 - (rect_title.h / 2) - 100; //y pos
    rect_title.x = W / 2 - (rect_title.w / 2); // x pos
    
    Font font_options("fonts/space_age.ttf", 30);
    Image play_blu(font_options.render("  Play", BLUE));
    Image rule_blu(font_options.render("  RULES", BLUE));
    Image scor_blu(font_options.render("  HIGHSCORE", BLUE));
    Image exit_blu(font_options.render("  EXIT", BLUE));

    Rect rect_play = play_blu.getRect();
    Rect rect_rule = rule_blu.getRect();
    Rect rect_scor = scor_blu.getRect();
    Rect rect_exit = exit_blu.getRect();

    int menu_option = 0;      //0 for play, 1 for exit
    int color_shift = 0;      //controls colorshift during mainmenu loop

    int key_press_delay = 0;
    
    while(1)
    {
        if (g == 176) color_shift = -2;
        if (g == 0) color_shift = 2;

        g += color_shift;
        
        Image play_red(font_options.render("< PLAY >", r, g, b));
        Image rule_red(font_options.render("< RULES >", r, g, b));
        Image scor_red(font_options.render("< HIGHSCORE >", r, g, b));
        Image exit_red(font_options.render("< EXIT >", r, g, b));

        // determine the colour and shape of the menu options
        rect_play = play_red.getRect();
        rect_rule = rule_red.getRect();
        rect_scor = scor_red.getRect();
        rect_exit = exit_red.getRect();
        
        // reposition the menu rects
        rect_play.x = W / 2 - (rect_play.w / 2);
        rect_play.y = rect_title.y + 175;
        rect_rule.x = rect_play.x;
        rect_rule.y = rect_play.y + 50;
        rect_scor.x = rect_play.x;
        rect_scor.y = rect_rule.y + 50;
        rect_exit.x = rect_play.x;
        rect_exit.y = rect_scor.y + 50;
        
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }
        
        keypress = get_keypressed();

        if (key_press_delay > 0 && key_press_delay < 10)
            ++key_press_delay;
        else key_press_delay = 0;
        
        if ((keypress[UPARROW] || keypress[w]) && menu_option > 0 &&
            key_press_delay == 0)
        {
            --menu_option;
            ++key_press_delay;
        }
        if ((keypress[DOWNARROW] || keypress[s]) && menu_option < 3 &&
            key_press_delay == 0)
        {
            ++menu_option;
            ++key_press_delay;
        }
        if (keypress[ESC]) menu_option = 3;

        switch(menu_option)
        {
            case 0:                
                // reposition galaxian select icon next to play option
                player_rect.x = rect_play.x - player_rect.w - 10;
                player_rect.y = rect_play.y + 5;
                break;
            case 1:                
                // reposition galaxian select icon next to exit option
                player_rect.x = rect_rule.x - player_rect.w - 10;
                player_rect.y = rect_rule.y + 5;
                break;
            case 2:                
                // reposition galaxian select icon next to exit option
                player_rect.x = rect_scor.x - player_rect.w - 10;
                player_rect.y = rect_scor.y + 5;
                break;
            case 3:                
                // reposition galaxian select icon next to exit option
                player_rect.x = rect_exit.x - player_rect.w - 10;
                player_rect.y = rect_exit.y + 5;
                break;
        }

        
        //lock surface and begin drawing
        surface.lock();
        
        surface.fill(BLACK);                         //refresh field
      
        galaxy.draw();                               //redraw stars
    
        surface.put_image(title, rect_title);        //redraw galaxian titlecard
        creator.draw(0);                             //draws creator info
        surface.put_image(player_ship, player_rect); //creates galaxian select icon

        // place menu options
        switch (menu_option)
        {
            case 0: // play game
                surface.put_image(play_red, rect_play);
                surface.put_image(rule_blu, rect_rule);
                surface.put_image(scor_blu, rect_scor);
                surface.put_image(exit_blu, rect_exit);
                break;
            case 1: // rules
                surface.put_image(play_blu, rect_play);
                surface.put_image(rule_red, rect_rule);
                surface.put_image(scor_blu, rect_scor);
                surface.put_image(exit_blu, rect_exit);
                break;
            case 2: // highscores
                surface.put_image(play_blu, rect_play);
                surface.put_image(rule_blu, rect_rule);
                surface.put_image(scor_red, rect_scor);
                surface.put_image(exit_blu, rect_exit);
                break;
            case 3: // exit game
                surface.put_image(play_blu, rect_play);
                surface.put_image(rule_blu, rect_rule);
                surface.put_image(scor_blu, rect_scor);
                surface.put_image(exit_red, rect_exit);
                break;
        }
        
        surface.unlock();
        surface.flip();
        delay(GAMESPEED);
        //unlock surface and finish drawing

        // create a KEYDOWN/KEYUP event to allow delay for pressing space key
        if ((keypress[SPACE] || keypress[ENTER]) && event.type() == KEYDOWN)
        {
            trigger = true;
        }
        
        if (event.type() == KEYUP && trigger)
        {
            switch(menu_option)
            {
                case 0:
                    play = true;
                    rules = false;
                    score = false;
                    exit = false;
                    return;
                case 1:
                    play = false;
                    rules = true;
                    score = false;
                    exit = false;
                    return;
                case 2:
                    play = false;
                    rules = false;
                    score = true;
                    exit = false;
                    return;
                case 3:
                    play = false;
                    rules = false;
                    score = false;
                    exit = true;
                    return;
            }
        }
    }
}


/*******************************************************************************
 --game_rules()--

 non interactive menu that gives the player the game rules
*******************************************************************************/
void game_rules(Surface & surface, KeyPressed & keypress, Event & event,
                Galaxy & galaxy, bool & rules, bool & exit)
{
    Font title("fonts/space_age.ttf",70);
    Image title_image(title.render("GAME RULES", RED));
    Rect title_rect = title_image.getRect();
    title_rect.x = W / 2 - (title_rect.w / 2);
    title_rect.y = 0;

    Font body("fonts/space_age.ttf", 30);
    Image body_image(body.render("Galaxi is a fast paced bullet-hell", YELLOW));
    Rect body_rect = body_image.getRect();
    body_rect.x = W / 2 - (body_rect.w / 2);
    body_rect.y = title_rect.y + title_rect.h + 10;

    Image body_image1(body.render("that requires constant vigilance!", YELLOW));
    Rect body_rect1 = body_image1.getRect();
    body_rect1.x = W / 2 - (body_rect1.w / 2);
    body_rect1.y = body_rect.y + body_rect.h + 10;

    Image body_image2(body.render("Be prepared for your enemies to be", YELLOW));
    Rect body_rect2 = body_image2.getRect();
    body_rect2.x = W / 2 - (body_rect2.w / 2);
    body_rect2.y = body_rect1.y + body_rect1.h + 20;

    Image body_image3(body.render("constantly firing and diving!", YELLOW));
    Rect body_rect3 = body_image3.getRect();
    body_rect3.x = W / 2 - (body_rect3.w / 2);
    body_rect3.y = body_rect2.y + body_rect2.h + 10;

    Image blue("images/galaxian/GalaxianAquaAlien.gif");
    Image red("images/galaxian/GalaxianRedAlien.gif");
    Image purple("images/galaxian/GalaxianPurpleAlien.gif");
    Image gold("images/galaxian/GalaxianFlagship.gif");

    int image_bounds_x = 100;
    int image_bounds_y = body_rect3.y + body_rect3.h + 30;
    int image_spacer = 100;
    Rect rect_blue = blue.getRect();
    Rect rect_red = red.getRect();
    Rect rect_purple = purple.getRect();
    Rect rect_gold = gold.getRect();

    rect_blue.x = image_bounds_x;
    rect_blue.y = image_bounds_y;
    rect_purple.x = image_bounds_x;
    rect_purple.y = rect_blue.y + rect_blue.h + image_spacer;
    rect_red.x = image_bounds_x;
    rect_red.y = rect_purple.y + rect_purple.h + image_spacer;
    rect_gold.x = image_bounds_x;
    rect_gold.y = rect_red.y + rect_red.h + image_spacer;

    Image blue_text(body.render("20 POINTS - LIKES TO SHOOT AND DIVE", WHITE));
    Rect blue_text_rect = blue_text.getRect();
    blue_text_rect.x = rect_blue.x + rect_blue.w + 30;
    blue_text_rect.y = rect_blue.y;

    Image red_text(body.render("50 POINTS - FORMATION AND SUICIDE DIVES", WHITE));
    Rect red_text_rect = blue_text.getRect();
    red_text_rect.x = rect_red.x + rect_red.w + 30;
    red_text_rect.y = rect_red.y;

    Image purple_text(body.render("75 POINTS - SHOOTS ALWAYS!", WHITE));
    Rect purple_text_rect = purple_text.getRect();
    purple_text_rect.x = rect_purple.x + rect_purple.w + 30;
    purple_text_rect.y = rect_purple.y;

    Image gold_text(body.render("100 POINTS - FORMATION DIVES", WHITE));
    Rect gold_text_rect = gold_text.getRect();
    gold_text_rect.x = rect_gold.x + rect_gold.w + 30;
    gold_text_rect.y = rect_gold.y;

    Image gold_text2(body.render("KILL FOR A CHANCE FOR AN EXTRA LIFE!", WHITE));
    Rect gold_text_rect2 = gold_text2.getRect();
    gold_text_rect2.x = rect_gold.x + rect_gold.w + 30;
    gold_text_rect2.y = gold_text_rect.y + gold_text_rect.h;

    Image cont(body.render("< PRESS SPACE TO CONTINUE >", YELLOW));
    Rect rect_cont = cont.getRect();
    rect_cont.y = gold_text_rect2.y + 70; //y pos
    rect_cont.x = W / 2 - (rect_cont.w / 2); // x pos

    bool trigger = false;
    while(1)
    {
        keypress = get_keypressed();
        
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }

        if ((keypress[SPACE] || keypress[ENTER] || keypress[ESC])
            && event.type() == KEYDOWN) trigger = true;
        if (event.type() == KEYUP && trigger)
        {
            rules = false;
            return;
        }

        surface.lock();
        surface.fill(BLACK);
      
        galaxy.draw();                               //redraw stars
        
        surface.put_image(title_image, title_rect);
        surface.put_image(body_image, body_rect);
        surface.put_image(body_image1, body_rect1);
        surface.put_image(body_image2, body_rect2);
        surface.put_image(body_image3, body_rect3);
        surface.put_image(blue, rect_blue);
        surface.put_image(purple, rect_purple);
        surface.put_image(red, rect_red);
        surface.put_image(gold, rect_gold);
        surface.put_image(blue_text, blue_text_rect);
        surface.put_image(red_text, red_text_rect);
        surface.put_image(purple_text, purple_text_rect);
        surface.put_image(gold_text, gold_text_rect);
        surface.put_image(gold_text2, gold_text_rect2);
        surface.put_image(cont, rect_cont);
        surface.unlock();
        surface.flip();
        delay(GAMESPEED);

    }
}

/*******************************************************************************
 --high_scores--

 menu that prints the highscores
*******************************************************************************/
void high_score(Surface & surface, KeyPressed & keypress, Event & event,
                Galaxy & galaxy, bool & exit, std::vector < int > & score)
{
    Font title("fonts/space_age.ttf",70);
    Image title_image(title.render("HIGHSCORES", RED));
    Rect title_rect = title_image.getRect();
    title_rect.x = W / 2 - (title_rect.w / 2);
    title_rect.y = 0;

    const int MAX_SCORE = 20;
    char Str_highscore0[MAX_SCORE];
    char Str_highscore1[MAX_SCORE];
    char Str_highscore2[MAX_SCORE];
    char Str_highscore3[MAX_SCORE];
    char Str_highscore4[MAX_SCORE];
    char Str_highscore5[MAX_SCORE];
    char Str_highscore6[MAX_SCORE];
    char Str_highscore7[MAX_SCORE];
    char Str_highscore8[MAX_SCORE];
    char Str_highscore9[MAX_SCORE];

    sprintf(Str_highscore0, "%d", score[0]);
    sprintf(Str_highscore1, "%d", score[1]); 
    sprintf(Str_highscore2, "%d", score[2]); 
    sprintf(Str_highscore3, "%d", score[3]);
    sprintf(Str_highscore4, "%d", score[4]);
    sprintf(Str_highscore5, "%d", score[5]);
    sprintf(Str_highscore6, "%d", score[6]);
    sprintf(Str_highscore7, "%d", score[7]);
    sprintf(Str_highscore8, "%d", score[8]);
    sprintf(Str_highscore9, "%d", score[9]); 
    
    //creator text;
    int spacer = 20;
    
    Font creator_font("fonts/space_age.ttf", 40);
    
    Image highscore_text0(creator_font.render(Str_highscore0, CYAN));
    Rect highscore_rect0 = highscore_text0.getRect();
    highscore_rect0.x = W / 2 - (highscore_rect0.w / 2);
    highscore_rect0.y = title_rect.y + title_rect.h + 50;

    Image highscore_text1(creator_font.render(Str_highscore1, CYAN));
    Rect highscore_rect1 = highscore_text1.getRect();
    highscore_rect1.x = highscore_rect0.x;
    highscore_rect1.y = highscore_rect0.y + highscore_rect0.h + spacer;
    
    Image highscore_text2(creator_font.render(Str_highscore2, CYAN));
    Rect highscore_rect2 = highscore_text2.getRect();
    highscore_rect2.x = highscore_rect1.x;
    highscore_rect2.y = highscore_rect1.y + highscore_rect1.h + spacer;

    Image highscore_text3(creator_font.render(Str_highscore3, CYAN));
    Rect highscore_rect3 = highscore_text3.getRect();
    highscore_rect3.x = highscore_rect2.x;
    highscore_rect3.y = highscore_rect2.y + highscore_rect2.h + spacer;

    Image highscore_text4(creator_font.render(Str_highscore4, CYAN));
    Rect highscore_rect4 = highscore_text4.getRect();
    highscore_rect4.x = highscore_rect3.x;
    highscore_rect4.y = highscore_rect3.y + highscore_rect3.h + spacer;

    Image highscore_text5(creator_font.render(Str_highscore5, CYAN));
    Rect highscore_rect5 = highscore_text5.getRect();
    highscore_rect5.x = highscore_rect4.x;
    highscore_rect5.y = highscore_rect4.y + highscore_rect4.h + spacer;

    Image highscore_text6(creator_font.render(Str_highscore6, CYAN));
    Rect highscore_rect6 = highscore_text6.getRect();
    highscore_rect6.x = highscore_rect5.x;
    highscore_rect6.y = highscore_rect5.y + highscore_rect5.h + spacer;

    Image highscore_text7(creator_font.render(Str_highscore7, CYAN));
    Rect highscore_rect7 = highscore_text7.getRect();
    highscore_rect7.x = highscore_rect6.x;
    highscore_rect7.y = highscore_rect6.y + highscore_rect6.h + spacer;

    Image highscore_text8(creator_font.render(Str_highscore8, CYAN));
    Rect highscore_rect8 = highscore_text8.getRect();
    highscore_rect8.x = highscore_rect7.x;
    highscore_rect8.y = highscore_rect7.y + highscore_rect7.h + spacer;

    Image highscore_text9(creator_font.render(Str_highscore9, CYAN));
    Rect highscore_rect9 = highscore_text9.getRect();
    highscore_rect9.x = highscore_rect8.x;
    highscore_rect9.y = highscore_rect8.y + highscore_rect8.h + spacer;

    Image numone_text(creator_font.render("1. ", YELLOW));
    Rect numone_rect = numone_text.getRect();
    numone_rect.x = highscore_rect0.x - 30 - numone_rect.w;
    numone_rect.y = highscore_rect0.y;

    Image numtwo_text(creator_font.render("2. ", YELLOW));
    Rect numtwo_rect = numtwo_text.getRect();
    numtwo_rect.x = numone_rect.x;
    numtwo_rect.y = highscore_rect1.y;

    Image numthree_text(creator_font.render("3. ", YELLOW));
    Rect numthree_rect = numthree_text.getRect();
    numthree_rect.x = numone_rect.x;
    numthree_rect.y = highscore_rect2.y;
    
    Image numfour_text(creator_font.render("4. ", YELLOW));
    Rect numfour_rect = numfour_text.getRect();
    numfour_rect.x = numone_rect.x;
    numfour_rect.y = highscore_rect3.y;

    Image numfive_text(creator_font.render("5. ", YELLOW));
    Rect numfive_rect = numfive_text.getRect();
    numfive_rect.x = numone_rect.x;
    numfive_rect.y = highscore_rect4.y;

    Image numsix_text(creator_font.render("6. ", YELLOW));
    Rect numsix_rect = numsix_text.getRect();
    numsix_rect.x = numone_rect.x;
    numsix_rect.y = highscore_rect5.y;

    Image numseven_text(creator_font.render("7. ", YELLOW));
    Rect numseven_rect = numseven_text.getRect();
    numseven_rect.x = numone_rect.x;
    numseven_rect.y = highscore_rect6.y;

    Image numeight_text(creator_font.render("8. ", YELLOW));
    Rect numeight_rect = numeight_text.getRect();
    numeight_rect.x = numone_rect.x;
    numeight_rect.y = highscore_rect7.y;

    Image numnine_text(creator_font.render("9. ", YELLOW));
    Rect numnine_rect = numnine_text.getRect();
    numnine_rect.x = numone_rect.x;
    numnine_rect.y = highscore_rect8.y;

    Image numten_text(creator_font.render("10. ", YELLOW));
    Rect numten_rect = numten_text.getRect();
    numten_rect.x = numone_rect.x;
    numten_rect.y = highscore_rect9.y;

    Font body("fonts/space_age.ttf", 30);
    Image cont(body.render("< PRESS SPACE TO CONTINUE >", YELLOW));
    Rect rect_cont = cont.getRect();
    rect_cont.y = H - rect_cont.h - 20; //y pos
    rect_cont.x = W / 2 - (rect_cont.w / 2); // x pos
    

    bool trigger = false;
    while(1)
    {
        keypress = get_keypressed();
        
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }

        if ((keypress[SPACE] || keypress[ENTER] || keypress[ESC])
            && event.type() == KEYDOWN) trigger = true;
        if (event.type() == KEYUP && trigger) return;

        surface.lock();
        surface.fill(BLACK);
       
        galaxy.draw();                               //redraw stars
        
        surface.put_image(title_image, title_rect);
        surface.put_image(numone_text, numone_rect);
        surface.put_image(numtwo_text, numtwo_rect);
        surface.put_image(numthree_text, numthree_rect);
        surface.put_image(numfour_text, numfour_rect);
        surface.put_image(numfive_text, numfive_rect);
        surface.put_image(numsix_text, numsix_rect);
        surface.put_image(numseven_text, numseven_rect);
        surface.put_image(numeight_text, numeight_rect);
        surface.put_image(numnine_text, numnine_rect);
        surface.put_image(numten_text, numten_rect);
        surface.put_image(highscore_text0, highscore_rect0);
        surface.put_image(highscore_text1, highscore_rect1);
        surface.put_image(highscore_text2, highscore_rect2);
        surface.put_image(highscore_text3, highscore_rect3);
        surface.put_image(highscore_text4, highscore_rect4);
        surface.put_image(highscore_text5, highscore_rect5);
        surface.put_image(highscore_text6, highscore_rect6);
        surface.put_image(highscore_text7, highscore_rect7);
        surface.put_image(highscore_text8, highscore_rect8);
        surface.put_image(highscore_text9, highscore_rect9);
        surface.put_image(cont, rect_cont);
        surface.unlock();
        surface.flip();
        delay(GAMESPEED);
    }
}

/*******************************************************************************
 --end_game()--

 End game function that executes when the number of player lives reaches 0
*******************************************************************************/
void end_game(Surface & surface, KeyPressed & keypress, Event & event,
              bool & exit)
{
    Font font("fonts/space_age.ttf", 70);
    Image text(font.render("GAME OVER", RED));
    Rect rect = text.getRect();
    rect.y = H / 2 - (rect.h / 2); //y pos
    rect.x = W / 2 - (rect.w / 2); // x pos

    Font font_cont("fonts/space_age.ttf", 30);
    Image cont(font_cont.render("< PRESS SPACE TO CONTINUE >", WHITE));
    Rect rect_cont = cont.getRect();
    rect_cont.y = rect.y + 100; //y pos
    rect_cont.x = W / 2 - (rect_cont.w / 2); // x pos

    bool trigger = false;
    while(1)
    {
        keypress = get_keypressed();
        
        if (event.poll() && event.type() == QUIT)
        {
            exit = true;
            return;
        }
        
        if ((keypress[SPACE] || keypress[ENTER] || keypress[ESC])
            && event.type() == KEYDOWN) trigger = true;
        if (event.type() == KEYUP && trigger) return;
        
        surface.lock();
        surface.put_image(text, rect);
        surface.put_image(cont, rect_cont);
        surface.unlock();
        surface.flip();
        delay(GAMESPEED);
    }
}


/*******************************************************************************
 --build_laser_array()--

 Populates a vector of Laser objects with a specified amount of lasers.
 The vector will expand to facilitate the population, but will then shrink to
 the size of the predetermined amount of objects.
*******************************************************************************/
void build_laser_array(Surface & surface, std::vector < Laser > & laser_array)
{
    int laser_ammount = 100;
    
    for (int i = 0; i < laser_ammount; ++i)
    {
        Laser laser(surface);
        laser_array.push_back(laser);
    }
    laser_array.shrink_to_fit();
}


/*******************************************************************************
 --fire()--

 Function that cycles through the laser_array vector, a object that is currently
 not "alive". It will then be switched to alive, and it will now be printed by
 the laser_array_draw() function, and moved by the laser_array_move() function.
*******************************************************************************/
void fire(std::vector < Laser > & laser_array, KeyPressed & keypress, Player & player)
{
    for (int i = 0; i < 100; ++i)
    {
        if (!laser_array[i].alive())
        {
            laser_array[i].player(true);
            laser_array[i].build(player.get_gun_x(), player.get_gun_y());
            laser_array[i].alive(true);
            
            return;
        }
    }    
}

bool collision(std::vector < Laser > & laser_array, Player & player,
               std::vector < Explosion > & explosion, int i)
{
    if ((laser_array[i].x() >= player.get_x() &&
         laser_array[i].x() <= player.get_x() + player.get_w()) &&
        (laser_array[i].y() >= player.get_y() &&
         laser_array[i].y() <= player.get_y() + player.get_h()) &&
        (laser_array[i].alive() && !laser_array[i].player()))
    {
        laser_array[i].alive(false);
        return true;
    }
    return false;
}

bool collision(std::vector < Alien_Red > & alien, Player & player, int i)
{
    if (i < 9)
    {
        if ((alien[i].x() >= player.get_x() &&
             alien[i].x() <= player.get_x() + player.get_w()) &&
            (alien[i].y() >= player.get_y() &&
             alien[i].y() <= player.get_y() + player.get_h()) &&
            alien[i].alive())
        {
            alien[i].alive(false);
            alien[i].dec_num();
           
            return true;
        }
    }
    return false;
}

bool collision(std::vector < Alien_Gold > & alien, Player & player, int i)
{
    if (i < 3)
    {
        if ((alien[i].x() >= player.get_x() &&
             alien[i].x() <= player.get_x() + player.get_w()) &&
            (alien[i].y() >= player.get_y() &&
             alien[i].y() <= player.get_y() + player.get_h()) &&
            alien[i].alive())
        {
            alien[i].alive(false);
            alien[i].dec_num();
            return true;
        }
    }
    return false;
}

bool collision(std::vector < Alien_Blue > & alien, Player & player, int i)
{
    if (i < 22)
    {
        if ((alien[i].x() >= player.get_x() &&
             alien[i].x() <= player.get_x() + player.get_w()) &&
            (alien[i].y() >= player.get_y() &&
             alien[i].y() <= player.get_y() + player.get_h()) &&
            alien[i].alive() && i < 22)
        {
            alien[i].alive(false);
            alien[i].dec_num();
            return true;
        }
    }
    return false;
}


/*******************************************************************************
 --laser_array_move()--

 Function that cycles through the laser array vecotr. Any object that is
 currently "alive" will execute the .move() method, and increment
*******************************************************************************/
void laser_array_move(std::vector < Laser > & laser_array, int i)
{
    laser_array[i].move();
}


/*******************************************************************************
 --laser_array_draw()--

 Function that cycles through the laser array vecotr. Any object that is
 currently "alive" will execute the .draw() method, and be placed on the surface
*******************************************************************************/
void laser_array_draw(std::vector < Laser > & laser_array, int i)
{
    laser_array[i].draw();
}


//void build_fleet(Surface & surface, std::vector < Alien_Blue > & fleet_blue)


void rebirth(std::vector < Alien_Blue > & fleet_blue,
             std::vector < Alien_Red > & fleet_red,
             std::vector < Alien_Gold > & fleet_gold,
             std::vector < Alien_Purple > & fleet_purple,
             int i)
{
    // std::cout << "begin rebirth\n";
    // std::cout << "Alien_Blue::num_aliens " << fleet_blue[0].get_num() << std::endl;
    // std::cout << "Alien_Red::num_aliens " << fleet_red[0].get_num() << std::endl;
    // std::cout << "Alien_Gold::num_aliens " << fleet_gold[0].get_num() << std::endl;
    // std::cout << "Alien_Purple::num_aliens " << fleet_purple[0].get_num() << std::endl;
    if (i < 22)
    {
        fleet_blue[i].alive(true);
        if (i < 11) fleet_blue[i].y(-100);
        if (i >= 11 && i < 22)
            fleet_blue[i].y(fleet_blue[0].y() + fleet_blue[0].h() + 10);
        fleet_blue[i].inc_num();
    }
    
    if (i < 9)
    {
        if (i < 3) fleet_red[i].y(-175);
        if (i >= 3 && i < 9) fleet_red[i].y(-210);
        fleet_red[i].alive(true);
        fleet_red[i].inc_num();
    }
    if (i < 3)
    {
        fleet_gold[i].y(-210);
        fleet_gold[i].alive(true);
        fleet_gold[i].inc_num();
    }
    if (i < 6)
    {
        fleet_purple[i].y(-150);
        fleet_purple[i].alive(true);
        fleet_purple[i].inc_num();
    }
    // std::cout << "end rebirth\n";
    // std::cout << "Alien_Blue::num_aliens " << fleet_blue[0].get_num() << std::endl;
    // std::cout << "Alien_Red::num_aliens " << fleet_red[0].get_num() << std::endl;
    // std::cout << "Alien_Gold::num_aliens " << fleet_gold[0].get_num() << std::endl;
    // std::cout << "Alien_Purple::num_aliens " << fleet_purple[0].get_num() << std::endl;
    
}

void reposition(std::vector < Alien_Blue > & fleet_blue,
                std::vector < Alien_Red > & fleet_red,
                std::vector < Alien_Gold > & fleet_gold,
                std::vector < Alien_Purple > & fleet_purple,
                int i)
{
    if (i < 11 && fleet_blue[i].y() < 200)
    {
        fleet_blue[i].y(fleet_blue[i].y() + 1);
    }
    if ((i >= 11 && i < 22) && fleet_blue[i].y() < 200 + fleet_blue[0].h() + 10)
    {
        fleet_blue[i].y(fleet_blue[i].y() + 1);
    }
    if (i < 9)
    {
        if (i < 3 && fleet_red[i].y() < 125)
            fleet_red[i].y(fleet_red[i].y() + 1);
        if ((i >= 3 && i < 9) && fleet_red[i].y() < 90)
            fleet_red[i].y(fleet_red[i].y() + 1);
    }
    if (i < 3 && fleet_gold[i].y() < 90)
        fleet_gold[i].y(fleet_gold[i].y() + 1);
    if (i < 6 && fleet_purple[i].y() < 150)
        fleet_purple[i].y(fleet_purple[i].y() + 1);
}
    
