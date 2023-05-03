//==============================================================================
#include "CApp.h"

//William
//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_QUIT) {
        Running = false;
    }
    if (Event->type == SDL_KEYDOWN)
    {
        switch (Event->key.keysym.sym)
        {
            //"Esc" to exit out 
        case SDLK_ESCAPE:
        {
            Running = false;
            break;
        }
        case SDLK_p:
        {
            if (!player.alive) 
            {
                reset();
            }
            break;
        }
        }
    }
}
//==============================================================================
