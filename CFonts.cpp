#include "CApp.h"

//Nolan
//==============================================================================
void CApp::displayGameStats(int x, int y, const char* formattedString, int number)
{
	SDL_DestroyTexture(messageTexture);
	SDL_FreeSurface(messageSurface);
	sprintf_s(message, formattedString, number);
	messageSurface = TTF_RenderText_Solid(font, message, color);
	messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
	messageRect = { x,y,texW, texH };
	SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
}