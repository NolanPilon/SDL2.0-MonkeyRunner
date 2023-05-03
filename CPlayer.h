#pragma once
//==============================================================================
#include <string.h>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "mywindow.h"
#include "SDL.h"
//==============================================================================

class CPlayer
{
public: 
	bool loaded;
	char imagename[255];
    int score = 0;
    int highScore = 0;
    bool alive = true;

	SDL_Rect position;
	SDL_FRect velocity;

    CPlayer(const char image[] = "", int x = 0, int y = 0, int h = 0, int w = 0, float vx = 0, float vy = 0)
    {
        strncpy_s(imagename, image, 255);
        position.x = x;
        position.y = y;
        position.h = h;
        position.w = w;
        velocity.x = vx;
        velocity.y = vy;
        loaded = false;
    }

    int loadPlayer(SDL_Renderer* prenderer);

    void display(SDL_Renderer* prenderer);
    void move();

    //Save stuff
    void saveScore();
    void loadScore();


protected:
    SDL_Texture* texture;
};
