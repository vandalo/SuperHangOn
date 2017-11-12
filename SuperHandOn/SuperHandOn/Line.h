#pragma once
#include "Globals.h"
#include <vector>

using namespace std;

class Line
{
public:
	float x, y, z; //3d center of line
	float X, Y, W; //screen coords
	float scale;
	float curve;
	int width = WIDTH;
	int height = HEIGHT;
	int roadW = ROADW;
	int segL = SEGL; //segmentLenght
	float camD = (float)CAMD; //camera depth

	Line() { curve = x = y = z = 0; X = 0; Y = SCREEN_HEIGHT; }

	//from world to scene
	void project(int camX, int camY, int camZ)
	{
		
		

		scale = camD / (z - camZ);
		X = (float)((1 + scale*(x - camX)) * width / 2);
		Y = (float)((1 - scale*(y - camY)) * height *0.55);
		W = (float)(scale * roadW * width / 2);
	}
};