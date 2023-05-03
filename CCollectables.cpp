#include "CCollectables.h"
#include "CApp.h"

//Williams
//==============================================================================

void CCollectables::move()
{
    SDL_Rect* p;
    SDL_FRect* v;

    p = &position;
    v = &velocity;

    p->x += v->x;
    p->y += v->y;
    if ((p->x < -1000))
    {
        p->x = rand() % 1200 + 900;
        p->y = rand() % 450;
        if (p->y < 386) 
        {
            p->y += 64;
        }
    }
    
}

//==============================================================================