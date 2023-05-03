#ifndef _CAPP_H_
#define _CAPP_H_

#define TICK_INTERVAL    10
#define NUM_SPRITES     1
#define MAX_SPEED       1
#define MAX_SPRITES 10
#define MAX_COINS 5

#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#include "mywindow.h"
#include "windows.h"
#include "xinput.h"
#include "SDL_ttf.h"
#include "SDL.h"



#include "Cplayer.h"
#include "CScroll_Player.h"
#include "CController.h"
#include "CProjectile.h"
#include "CNpc.h"
#include "CCollectables.h"

using namespace std;
//==============================================================================

class CApp
{
private:
    bool Running;
    bool broken = false;

    Uint32 next_time;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Controller* xboxController = new Controller;
    TTF_Font* font;
    SDL_Color color;
    SDL_Color color1;
    char message[100];
    SDL_Surface* messageSurface;
    SDL_Texture* messageTexture;
    SDL_Rect messageRect;

    CPlayer player;
    CProjectile missiles[MAX_SPRITES];
    CScroll_Player forest;
    CNpc npc[3];
    CCollectables coins[MAX_COINS];

    XINPUT_STATE controllerState;
    XINPUT_VIBRATION vibration;
    bool ControllerConnected;

public:
    CApp();
    Uint32 time_left(void);
    int OnExecute();

    //Distance stuff
    int tickTimer = 0;
    int travelDistance = 10;

    //Difficulty Variables
    int scrollSpeed = 2;


public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();
    bool check_collision(SDL_Rect A, SDL_Rect B);
    void resetCoins();
    int LoadSprite(char *file, SDL_Texture **psprite, SDL_Rect *prect);
    void MoveSprites();
    void reset();

    void displayGameStats(int x, int y, const char* formattedString, int number);
    void displayGameOver(int x, int y, const char* formattedString);

    void OnCleanup();

};

//==============================================================================

#endif
