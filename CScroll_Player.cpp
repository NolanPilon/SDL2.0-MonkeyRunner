#include "CScroll_Player.h"
#include "CApp.h"

//Nolan
//==============================================================================

CScroll_Player::CScroll_Player()
{
    //constructor
}

CScroll_Player::~CScroll_Player()
{
    //destructor
}

//==============================================================================

void CScroll_Player::display(SDL_Renderer* prenderer)
{
    SDL_RenderCopy(prenderer, texture, &src, &destscr);
}

//==============================================================================

int CScroll_Player::loadPlayer(SDL_Renderer* prenderer)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);

    destscr.x = 0;
    destscr.y = 0;
    destscr.h = 0;
    destscr.w = 0;

    velocity.x = 2;
    velocity.y = 0;

    return (retval);
}

//==============================================================================

void CScroll_Player::move()
{
    src.x += velocity.x;
    src.y += velocity.y;

    if (src.x >= window_w)
    {
        src.x = 0;
    }
}
//==============================================================================