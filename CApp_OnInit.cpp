//==============================================================================
#include "CApp.h"


bool CApp::OnInit()
{
    //Nolan
    //==============================================================================
    xboxController->displayController();


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("Group lab Nolan-Xander-Will",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    srand(time(NULL));

    //Init fonts
    TTF_Init();
    font = TTF_OpenFont("pixel-font.ttf", 24);
    color = { 255,255,255 };
    color1 = { 255,0,0 };

    //init background
    strncpy_s(forest.imagename, "sprites\\forest.bmp", 255);
    forest.loadPlayer(renderer);
    forest.set_scroll_loc(0, 0, window_w, window_h);
    forest.destscr.h = window_h;
    forest.destscr.w = window_w;

    //William
    //==============================================================================
    //init player
    strncpy_s(player.imagename, "sprites\\monkey_ground.bmp", 255);
    player.loadPlayer(renderer);
    player.position.x = WINDOW_WIDTH /6;
    player.position.y = 200;
    player.position.h = 52;
    player.position.w = 50;
    player.velocity.x = 0;
    player.velocity.y = 0;

    //Nolan
    //==============================================================================
    //init NPCs
    for (int i = 0; i < 3; i++) 
    {
        strncpy_s(npc[i].imagename, "sprites\\guy.bmp", 255);
        npc[i].loadPlayer(renderer);
    }
    
    npc[0].spawnNpc(window_w / 2 + 32, window_h - 168, -2);
    npc[1].spawnNpc(window_w / 2 + 128, window_h - 168, -2);
    npc[2].spawnNpc(window_w / 2 + 296, window_h - 168, -2);

    //init coins (renderer,dw,dh,x,y,speed) 
    //William
    //==============================================================================

    for (int i = 0; i < MAX_COINS; i++)
    {
        strncpy_s(coins[i].imagename, "sprites\\coin.bmp", 255);
    }
    coins[0].loadPlayer(renderer, 64, 64, rand() % 1200 + 900, rand() % 386, -scrollSpeed - 1);
   
    for (int i = 1; i < MAX_COINS; i++)
    {
        coins[i].loadPlayer(renderer, 64, 64, coins[i - 1].position.x + 38, coins[i - 1].position.y, coins[i - 1].velocity.x);
    }

    for (int i = 0; i < MAX_SPRITES; i++)
    {
        strncpy_s(missiles[i].imagename, "sprites\\spear.bmp", 255);
    }

    // creates missiles (renderer,dw,dh,x,y,speed)

    missiles[0].loadPlayer(renderer, 124, 32, 800, 100, -scrollSpeed -1);
    for (int i = 1; i < MAX_SPRITES; i++)
    {
        missiles[i].loadPlayer(renderer, 124, 32, 1000, 400, 0.0f);
       
    }

    //Load HighScore --Nolan
    //==============================================================================
    player.loadScore();
    
    return true;
}
//==============================================================================
