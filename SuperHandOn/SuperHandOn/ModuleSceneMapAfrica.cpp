#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMapAfrica.h"
#include "ModulePlayer.h"
#include "Line.h"

ModuleSceneMapAfrica::ModuleSceneMapAfrica(bool active) : ModuleSceneTrack(active)
{
	background = { 17, 61, 640, 275 };
	backgroundParalax = { 668,98,625,28 };
	backgroundTrackName = { 266, 467,98,18 };


	grass1 = Color(224, 240, 160, 255);
	grass2 = Color(192, 192, 128, 255);
	rumble1 = Color(128, 128, 128, 255);
	rumble2 = Color(225, 225, 225, 255);
	color_road = Color(192, 192, 160, 255);
	color_line = Color(255, 255, 255, 255);

	
	//pos = 1200000;
	pos = 0;
	playerX = 0;
}

bool ModuleSceneMapAfrica::Start(){
	ModuleSceneTrack::Start();
	bool up = true;
	bool endY = false;
	int count = 0; int count2 = 0;
	float lastValue = 0;
	bool mustAlign = false;
	for (int i = 0; i < 40000; i++)
	{
		Line line;
		line.z = (float)i * line.segL;

		if (i > 300 && i < 500) line.curve = -2;
		else if (i > 600 && i < 850) line.curve = -2;
		else if (i > 900 && !endY) {
			line.curve = 3;
			if (up) {
				line.y = lines[i - 1].y + 20;
				if (line.y > 3000) up = false;
			}
			else {
				if (line.y < 2800) line.y = lines[i - 1].y - 5;
				else line.y = lines[i - 1].y - 20;
				if (line.y < 0) {
					endY = true;
					line.y = 0;
				}
			}
		}
		//Ends at 1700
		else if (i > 1700 && i < 2000) line.curve = -4;
		else if (i > 2250 && count < 3) {
			mustAlign = true;
			if (count == 0) line.curve = -1;
			else if (count == 1) line.curve = -4;
			else line.curve = 2.5;
			float newValue = (float)(sin(i / 60.0) * 750);
			if (lastValue < 0 && newValue > 0) count++;
			line.y = newValue;
			lastValue = line.y;
			if (count == 3) {
				lastValue = 0;
				mustAlign = false;
			}
		}
		//ends at 3100
		else if (i > 3100 && i < 3200)  line.curve = 3;
		else if (i > 3200 && i < 3400) line.curve = -1;
		else if (i > 3400 && i < 3500)  line.curve = -4;
		else if (i > 3500 && i < 3900)  line.curve = 2;
		else if (i > 4000 && i < 4200)  line.curve = -2;
		else if (i > 4250 && i < 4500)  line.curve = 4;
		else if (i > 4700 && i < 4900)  line.curve = 1;
		else if (i > 5000 && i < 5200)  line.curve = -3;
		//else if (i > 5250 && i < 5400)  line.curve = 2;
		else if (i > 5280 && count2 < 4) {
			if (i > 5500 && i < 5600)  line.curve = 4;
			else if (i > 5900 && i < 6200)  line.curve = -3;
			float newValue = (float)(sin(i / 30.0) * 1500);
			if (lastValue < 0 && newValue > 0) count2++;
			line.y = newValue;
			lastValue = line.y;
		}
		//ends at 6100
		else if (i > 5900 && i < 6200)  line.curve = -3;
		//HERE SWAP MAP!
		else if (i > 6200 && i < 6300) line.y = lines[i - 1].y + 100;
		//else if (i > 6400 && i < 6600)  line.curve = 2;

		else if (i >= 6300 && i < 7000)
			line.y = lines[i - 1].y - 5;
		if (line.y < 0 && mustAlign) {
			line.y++;
			if (line.y > 0) {
				line.y = 0;
				mustAlign = false;
			}
		}

		if (line.y > 0 && mustAlign) {
			line.y--;
			if (line.y < 0) {
				line.y = 0;
				mustAlign = false;
			}
		}
		//Decoration
		if (i % 10 == 0) {
			line.id = deadTree;
			int negate = (int)(rand() % 2);
			if (negate == 0) negate = -1;
			line.spriteX = (rand() % (int)(decoration[deadTree]->maxX) + decoration[deadTree]->minX)*negate;
		}

		//StartSign
		/*if (i == 12) {
			line.id = startSign;
			line.spriteX = 0;
		}*/

		lines.push_back(line);
		
	}

	N = lines.size();
	return true;
}

ModuleSceneMapAfrica::~ModuleSceneMapAfrica()
{}
