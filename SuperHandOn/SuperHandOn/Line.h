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

	int id;
	int spriteX;
	float clip;

	int width = WIDTH;
	int height = HEIGHT;
	int roadW = ROADW;
	int segL = SEGL; //segmentLenght
	float camD = (float)CAMD; //camera depth
	
	Line() {
		curve = x = y = z = 0; X = 0; Y = 0; W = 0;
		spriteX = id = -1; clip = 0; scale = 0;
	}

	//from world to scene
	void project(int camX, int camY, int camZ)
	{
		scale = camD / (z - camZ);
		X = (float)((1 + scale*(x - camX)) * width / 2);
		Y = (float)((1 - scale*(y - camY)) * height * 0.55);
		W = (float)(scale * roadW * width / 2);
	}

	void DrawObject(SDL_Rect sprite, SDL_Texture* tex, float position = 999)
	{
		float spriteXToDraw = spriteX;
		if(position != 999) spriteXToDraw = position;
		int w = sprite.w;
		int h = sprite.h;
		float destX = X + scale * spriteXToDraw * width / 2;
		float destY = Y + 4;
		float destW = w * W / 266;
		float destH = h * W / 266;

		destX += destW * spriteXToDraw; //offsetX
		destY += destH * (-1);    //offsetY

		float clipH = destY + destH - clip;
		if (clipH<0) clipH = 0;

		
		destX = X + (W * spriteXToDraw);
		if (clipH >= destH) return;

		sprite.h = (int)(h - h*clipH / destH);
		int spriteScaleH = (int)(sprite.h*(destH / h));
		App->renderer->Blit(tex, (int)destX, (int)destY, &sprite, 0.f, false, false, (int)(sprite.w*(destW / w)), spriteScaleH);
	}

};