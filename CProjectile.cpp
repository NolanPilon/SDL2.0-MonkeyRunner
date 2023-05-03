#include "CProjectile.h"
#include "CApp.h"

//William
//==============================================================================
int CProjectile::loadPlayer(SDL_Renderer* renderer, int dw, int dh, int x, int y, float vx)
{
    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(imagename);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", imagename, SDL_GetError());
        return (-1);
    }

    position.w = dw;
    position.h = dh;
    position.x = x;
    position.y = y;
    velocity.x = vx;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8*)temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint16*)temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16*)temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint32*)temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32*)temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }

    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

//==============================================================================

void CProjectile::move(int scrollSpeed)
{
    SDL_Rect* p;
    SDL_FRect* v;

    p = &position;
    v = &velocity;

    p->x += v->x;

    if (p->x <= (-200))
    {
        v->x = ((rand() % 5+1) * -1) - scrollSpeed;
        p->x = window_w + 100;
    }
}

//==============================================================================