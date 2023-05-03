#pragma once
#include "windows.h"
#include "xinput.h"

#pragma once

class Controller
{

public:
	Controller();
	~Controller();

	void displayController();
	void getInput();

	bool IsAPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A); }

private:
	XINPUT_STATE controllerState;
	XINPUT_VIBRATION vibration;

};