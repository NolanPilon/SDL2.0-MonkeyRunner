//==============================================================================
//Game210 - Final Lab - Rocket Monkey
//4/28/2022 Nolan-Xander-William
//==============================================================================
#include "CApp.h"
//==============================================================================

CApp::CApp()
{
    Running = true;
}

//==============================================================================

Uint32 CApp::time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

//==============================================================================

int CApp::LoadSprite(char *file, SDL_Texture **psprite, SDL_Rect *prect)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
        return (-1);
    }

    prect->w = temp->w;
    prect->h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    *psprite = SDL_CreateTextureFromSurface(renderer, temp);
    if (!*psprite)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }

    SDL_FreeSurface(temp);

    return (0);
}

//==============================================================================

int CApp::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

    SDL_Event Event;
    next_time = SDL_GetTicks() + TICK_INTERVAL;
    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

//William
//==============================================================================
bool CApp::check_collision(SDL_Rect A, SDL_Rect B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {

        return false;
    }
    if (rightA <= leftB)
    {

        return false;
    }
    if (leftA >= rightB)
    {

        return false;
    }
    if (topA >= bottomB)
    {

        return false;
    }
    //If none of the sides from A are outside B
    return true;
}

//William
//=============================================================================
void CApp::displayGameOver(int x, int y, const char* formattedString)
{

    //To cleanup memory
    SDL_DestroyTexture(messageTexture);												
    SDL_FreeSurface(messageSurface);

    sprintf_s(message, formattedString);	 										

    messageSurface = TTF_RenderText_Solid(font, message, color1);					
    messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);		

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);						
    messageRect = { x, y, texW, texH };												

    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);					
}
//==============================================================================

//William
//==============================================================================
void::CApp::resetCoins()
{
    for (int i = 1; i < MAX_COINS; i++)
    {
        coins[i].position.x = coins[i - 1].position.x + 38;
        coins[i].position.y = coins[i - 1].position.y;
        coins[i].velocity.x = coins[i - 1].velocity.x;
    }
}

int main(int argc, char* argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}

//William
//==============================================================================
void CApp::reset() 
{
    //resets everything
    scrollSpeed = 2;
    player.score = 0;
    player.alive = true;
    travelDistance = 0;
    broken = false;
    //player
    player.position.x = WINDOW_WIDTH / 6;
    player.position.y = 200;
    player.position.h = 52;
    player.position.w = 50;
    player.velocity.x = 0;
    player.velocity.y = 0;
    //npc
    npc[0].spawnNpc(window_w / 2 + 32, window_h - 168, -2);
    npc[1].spawnNpc(window_w / 2 + 128, window_h - 168, -2);
    npc[2].spawnNpc(window_w / 2 + 296, window_h - 168, -2);
    for (int i = 0; i < 3; i++)
    {
        npc[i].velocity.x = -scrollSpeed;
    }
    //coins
    coins[0].position.x = rand() % 1200 + 900;
    coins[0].position.y = rand() % 386;
    coins[0].velocity.x = -scrollSpeed;
    resetCoins();
    //background
    forest.velocity.x = scrollSpeed;
    //missiles
    missiles[0].velocity.x = -scrollSpeed - 1;
    missiles[0].position.x = 1000;
    for (int i = 1; i < MAX_SPRITES; i++)
    {
        missiles[i].velocity.x = 0;
        missiles[i].position.x = 1000;
    }
    player.loadScore();
}

//==============================================================================
