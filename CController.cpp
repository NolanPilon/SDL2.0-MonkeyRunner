#include "CController.h"
#include <iostream>

//Nolan
//==============================================================================
Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::displayController()
{
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
	XInputGetState(0, &controllerState);
	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
	{
		printf("Controller Connected\n");
	}
}

void Controller::getInput() 
{
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
	XInputGetState(0, &controllerState);
}