#include "CNpc.h"
#include "CApp.h"

//Nolan
//==============================================================================
void CNpc::spawnNpc(int x, int y, float v)
{
	position.x = x;
	position.y = y;
	velocity.x = v;
}

void CNpc::move()
{
    SDL_Rect* p;
    SDL_FRect* v;

    p = &position;
    v = &velocity;

    p->x += v->x;
    p->y += v->y;
    if ((p->y >= (window_h - 146)) || p->y < 0)
    {
        v->y = 0;
    }

    v->y += 0.2f;
}
