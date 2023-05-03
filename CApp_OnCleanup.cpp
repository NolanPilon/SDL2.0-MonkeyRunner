//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {
    //Nolan
    //Free pointers
    messageSurface = NULL;
    messageTexture = NULL;
    font = NULL;
    window = NULL;
    renderer = NULL;

    //Close subsystems
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_CloseAudio();
    SDL_JoystickClose(0);
    SDL_Quit();
}

//==============================================================================
