#pragma once
#include "CPlayer.h"
class CProjectile :
    public CPlayer
{
public:
    //SDL_FRect position;
    CProjectile(const char image[] = "", int x = -100, int y = -100, int h = 0, int w = 0, float vx = 0, float vy = 0)
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
    // void setStats(int x = 0, int y = 0, int vx = 0);
    int loadPlayer(SDL_Renderer* renderer, int dw, int dh, int x, int y, float vx);
    void move(int scrollSpeed);
};