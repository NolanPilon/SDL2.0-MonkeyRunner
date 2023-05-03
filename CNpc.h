#pragma once
#include "CPlayer.h"

class CNpc : public CPlayer 
{
public:
	void spawnNpc(int x, int y, float v);
	void move();
};