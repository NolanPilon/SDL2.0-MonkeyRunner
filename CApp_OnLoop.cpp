//==============================================================================
#include "CApp.h"
//==============================================================================

void CApp::MoveSprites()
{
    forest.move();
    forest.display(renderer);
    player.display(renderer);
    player.move();

    //display missiles
    // William
    //==============================================================================
    for (int i = 0; i < MAX_SPRITES; i++)
    {
        // if off screne mimic player's height
        if (missiles[i].position.x > window_w)
        {
            missiles[i].position.y = player.position.y;
        }
        missiles[i].move(scrollSpeed);
        missiles[i].display(renderer);
    }

    //display Coins
    for (int i = 0; i < MAX_COINS; i++)
    {

        coins[i].display(renderer);
        coins[i].move();
    }

    //display npc
    // Nolan
    //==============================================================================
    for (int i = 0; i < 3; i++)
    {
        npc[i].display(renderer);
        npc[i].move();
    }

}

//==============================================================================

void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    //ControllerStuff
    // Nolan
    //==============================================================================
    xboxController->getInput();
    if (xboxController->IsAPressed() && player.alive == true)
    {
        player.velocity.y -= 0.5f;
    }

    //Game Timer
    tickTimer++;

    if (tickTimer % 100 == 0)
    {
        tickTimer = 0;
        if (player.alive == true)
        {
            travelDistance += 10;
        }
    }

    if (travelDistance % 100 == 0 && tickTimer == 0 && player.alive == true)
    {
        scrollSpeed += 1;
        forest.velocity.x = scrollSpeed;
        for (int i = 0; i < 3; i++)
        {
            npc[i].velocity.x = -scrollSpeed;
        }
    }

    MoveSprites();

    //William
    //==============================================================================
    for (int i = 0; i < MAX_SPRITES; i++)
    {
        //Check if the player got hit
        if (check_collision(missiles[i].position, player.position) == true)
        {
            player.alive = false;
        }

        //Checks of a missile is inside of another missile
        if (missiles[i].position.x > window_w)
        {
            if (check_collision(missiles[i].position, missiles[i + 1].position) == true)
            {
                missiles[i + 1].position.x += 32;
            }
        }
    }


    //NPC kicking
    // Nolan
    //==============================================================================
    for (int i = 0; i < 3; i++)
    {
        if (check_collision(player.position, npc[i].position) && player.alive == true)
        {
            npc[i].velocity.x += scrollSpeed * 10.0f;
            npc[i].velocity.y -= rand() % 20 + 10;
            player.score += 50;
        }

        if (npc[i].position.x > window_w + 64 && npc[i].position.y < window_h - 146 || npc[i].position.x < -64)
        {
            npc[i].position.x = rand() % 1200 + 900;
            npc[i].velocity.x = -scrollSpeed;
        }
    }


    //William
    // Coin check
    //==============================================================================
    for (int i = 0; i < MAX_COINS; i++)
    {
        coins[i].velocity.x = -scrollSpeed;

        if (check_collision(coins[i].position, player.position) == true && player.alive)
        {
            coins[i].position.x = -64;
            coins[i].velocity.x = 0;
            player.score += 100;
        }
        //resets coins when last one is offscrn
        if (coins[MAX_COINS - 1].position.x < -275)
        {
            resetCoins();
        }
    }

    //death screne
    if (player.alive == false)
    {
        //Save Score
        player.saveScore();

        // freeze everything on screen
        for (int i = 0; i < NUM_SPRITES; ++i)
        {
            //liquid.velocity.x = 0;
            //logs[i].velocity.x = 0;
            //cars[i].velocity.x = 0;
            //gameOver = true;
        }

        displayGameOver(window_w / 2 - 70, window_h / 2 - 100, "GAME OVER");
        displayGameStats((window_w / 4) + 50, window_h / 2, "Press 'P' to Play Again", NULL);
        displayGameStats(window_w / 4 + 80, window_h / 2 + 100, "Press 'ESC' to EXIT", NULL);

        //stops missiles from respawning 
        for (int i = 0; i < MAX_SPRITES; i++)
        {
            if (missiles[i].position.x <= -192)
            {
                missiles[i].velocity.x = 0;
            }
        }
        //stops coins from respawning
        for (int i = 0; i < MAX_COINS; i++)
        {
            if (coins[i].position.x <= -100)
            {
                coins[i].velocity.x = 0;
            }
        }
        //stops npc from respawning
        for (int i = 0; i < 3; i++)
        {
            if (npc[i].position.x <= -64 || npc[i].position.x >= window_w)
            {
                npc[i].velocity.x = 0;
            }
        }

        //freeze background
        if (broken == false)
        {
            try
            {
                do {
                    forest.velocity.x -= 2;
                    if (forest.velocity.x < 0)
                    {
                        forest.velocity.x = 0;
                    }

                } while (forest.velocity.x = 0);
                throw forest.velocity.x;
            }
            catch (float)
            {
                broken = true;
                printf("Error : %f", forest.velocity.x);
            }
        }   
    }
    //difficulty scaling
    // William
    //==============================================================================
     
    switch (travelDistance)
    {
    case 1500:
    {
        missiles[7].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
        missiles[8].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
        missiles[9].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
    }
    case 700:
    {
        missiles[5].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
        missiles[6].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
    }
    case 400:
    {
        missiles[3].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
        missiles[4].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;
    }
    case 100:
    {   
        missiles[1].velocity.x = ((rand() % 5+ 1) * -1) - scrollSpeed;
        missiles[2].velocity.x = ((rand() % 5 + 1) * -1) - scrollSpeed;  
    }
        break;
    }
    
    //==============================================================================
    //Display Stats
    // Nolan
    //==============================================================================
    displayGameStats(20, 20, "Distance: %3d M", travelDistance);
    displayGameStats(window_w - 200, 20, "Score: %3d", player.score);
    displayGameStats(window_w - 232, 40, "High Score: %3d", player.highScore);
}

//==============================================================================