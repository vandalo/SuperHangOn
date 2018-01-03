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

using namespace std;

ModuleSceneMapAfrica::ModuleSceneMapAfrica(bool active) : ModuleSceneTrack(active)
{
	background = { 17, 61, 640, 275 };
	backgroundParalax = { 668,98,625,28 };
	backgroundTrackName = { 266, 467,98,18 };

	grass1 = Color(224, 240, 160, 255);
	grass2 = Color(192, 192, 128, 255);
	rumble1 = Color(128, 128, 128, 255);
	rumble2 = Color(225, 225, 225, 255);
	color_road1 = Color(192, 192, 160, 255);
	color_road2 = Color(192, 192, 160, 255);
	color_line1 = Color(255, 255, 255, 255);
	color_line2 = Color(192, 192, 160, 255);
	sky = Color(128, 224, 224, 255);
	
	//pos = 1200000;
	pos = 0;
	playerX = 0;

}

bool ModuleSceneMapAfrica::Start(){
	ModuleSceneTrack::Start();

	//Create bioms
	Bioma *biomaDesert = new Bioma();
	biomaDesert->grass1 = Color(224, 240, 160, 255);
	biomaDesert->grass2 = Color(192, 192, 128, 255);
	biomaDesert->rumble1 = Color(128, 128, 128, 255);
	biomaDesert->rumble2 = Color(225, 225, 225, 255);
	biomaDesert->color_road1 = Color(192, 192, 160, 255);
	biomaDesert->color_road2 = Color(192, 192, 160, 255);
	biomaDesert->color_line1 = Color(255, 255, 255, 255);
	biomaDesert->color_line2 = Color(192, 192, 160, 255);
	biomaDesert->sky = Color(128, 224, 224, 255);

	biomaDesert->background = { 17, 61, 640, 275 };
	biomaDesert->backgroundParalax = { 668,98,625,28 };
	bioms.push_back(biomaDesert);
	desertBiom = bioms.size() - 1;

	Bioma *biomaMountain = new Bioma();
	biomaMountain->grass1 = Color(181, 201, 27, 255);
	biomaMountain->grass2 = Color(216, 232, 25, 255);
	biomaMountain->rumble1 = Color(255, 104, 7, 255);
	biomaMountain->rumble2 = Color(243, 240, 215, 255);
	biomaMountain->color_road1 = Color(172, 208, 176, 255);
	biomaMountain->color_road2 = Color(142, 171, 145, 255);
	biomaMountain->color_line1 = Color(172, 208, 176, 255);
	biomaMountain->color_line2 = Color(142, 171, 145, 255);
	biomaMountain->sky = Color(96, 32, 224, 255);

	biomaMountain->background = { 1326, 550, 640, 275 };
	biomaMountain->backgroundParalax = { 1340,79,640,45 };
	bioms.push_back(biomaMountain);
	mountainBiom = bioms.size() - 1;

	Bioma *biomaDesert2 = new Bioma();
	biomaDesert2->grass1 = Color(253, 243, 139, 255);
	biomaDesert2->grass2 = Color(219, 210, 101, 255);
	biomaDesert2->rumble1 = Color(251, 247, 249, 255);
	biomaDesert2->rumble2 = Color(148, 162, 0, 255);
	biomaDesert2->color_road1 = Color(250, 208, 66, 255);
	biomaDesert2->color_road2 = Color(222, 169, 0, 255);
	biomaDesert2->color_line1 = Color(250, 208, 66, 255);
	biomaDesert2->color_line2 = Color(222, 169, 0, 255);
	biomaDesert2->sky = Color(64, 32, 224, 255);

	biomaDesert2->background = { 1323, 1040, 640, 275 };
	biomaDesert2->backgroundParalax = { 1338,133,640,45 };
	bioms.push_back(biomaDesert2);
	desert2Biom = bioms.size() - 1;

	currentBiomId = desertBiom;
	bool up = true;
	bool endY = false;
	int count = 0; int count2 = 0;
	float lastValue = 0;
	bool mustAlign = false;
	stageTimeSaved.clear();
	bestScores.clear();

	//Load segments times
	ifstream myScore;
	string input;
	myScore.open("level/africaStageTime.txt");
	getline(myScore, input);
	int seg = stoi(input);
	for (int i = 0; i < seg; i++) {
		getline(myScore, input);
		stageTimeSaved.push_back(stof(input));
	}

	myScore.close();

	//Load Best Scores
	ifstream myBestScore;
	myBestScore.open("level/africaBestScores.txt");
	for (int i = 0; i < 8; i++) {
		Score score_tmp;
		getline(myBestScore, input);
		score_tmp.score = stof(input);
		getline(myBestScore, input);
		score_tmp.stage = stoi(input);
		getline(myBestScore, input);
		score_tmp.name = input;
		getline(myBestScore, input);
		score_tmp.time = stof(input);
		bestScores.push_back(score_tmp);
	}
	myBestScore.close();

	//Create the track
	for (int i = 0; i < 10; i++) {
		Line line;
		line.z = (float)lines.size() * line.segL;
		lines.push_back(line);
	}
	int startSignPos = 10, oldIdDecoration;
	bool setSwapBiom = false;
	ifstream myfile;

	myfile.open("level/africa.txt");
	if (myfile.is_open())
	{
		
		getline(myfile, input);
		getline(myfile, input);
		startSignPos = stoi(input);

		//LoadBiomSquence
		getline(myfile, input);
		getline(myfile, input);
		int numBioms = stoi(input);
		for (int i = 0; i < numBioms; i++) {
			getline(myfile, input);
			int idBiom = 0;
			if (input == "desertBiom")
				idBiom = desertBiom;
			else if (input == "mountainBiom")
				idBiom = mountainBiom;
			else if (input == "desert2Biom")
				idBiom = desert2Biom;
			biomsSequence.push_back(idBiom);
		}
		//CREATE ROAD
		while (getline(myfile, input))
		{
			if (input[0] == '{') getline(myfile, input);
			float length, curve, climb, decFreq;
			int randomPosition, position, decorationId;
			string ;
			length = (float)stoi(input);
			getline(myfile, input);
			curve = (float)stoi(input);
			getline(myfile, input);
			if (input[0] == '*') {
				setSwapBiom = true;
				input.erase(0,1);
			}
			climb = (float)stoi(input);
			getline(myfile, input);
			//GetId
			decorationId = 0;
			if (input == "signLeft")
				decorationId = signLeft;
			else if (input == "signRight")
				decorationId = signRight;
			else if (input == "deadTree")
				decorationId = deadTree;
			else if (input == "tonnel")
				decorationId = tonnel;
			else if (input == "bidalstone")
				decorationId = bidalstone;
			else if (input == "checkSign")
				decorationId = checkSign;
			else if (input == "rock")
				decorationId = rock;
			else if (input == "changeBiom")
				decorationId = biomSwapPoint;
			else if (input == "bushTree")
				decorationId = bushTree;
			else if (input == "birdbird")
				decorationId = birdbird;
			else if (input == "palmTree")
				decorationId = palmTree;
			else if (input == "cactus")
				decorationId = cactus;
			else if (input == "goalSign")
				decorationId = goalSign;
			else if (input == "people")
				decorationId = people;
			getline(myfile, input);
			decFreq = (float)stoi(input);
			getline(myfile, input);
			randomPosition = stoi(input);
			getline(myfile, input);
			position = stoi(input);


			for (int i = 0; i < length - 1; i++) {
				Line line;
				line.z = (float)lines.size() * line.segL;
				line.curve = curve;
				if (climb > 0) {
					if (i < length / 2) {
						line.y = lines[lines.size() - 1].y + (climb * (i / (length / 2)));
						if (setSwapBiom == true) {
							setSwapBiom = false;
							oldIdDecoration = decorationId;
							decorationId = biomSwapPoint;
						}
					}
					else 
						line.y = lines[lines.size() - 1].y + (climb * (2 - (i / (length / 2))));
				}
				else if (climb < 0) {
					line.y = lines[lines.size() - 1].y += (float)(sin(i / 30.0) * (climb * -1));
				}

				else line.y = lines[lines.size() - 1].y;
				if (decFreq != 0 && i % (int)decFreq == 0) {
					line.id = decorationId;
					if (randomPosition == 2) {
						int negate = (int)(rand() % 2);
						if (negate == 0) negate = -1;
						line.spriteX = (rand() % (int)(decoration[deadTree]->maxX) + decoration[deadTree]->minX)*negate;
					}
					else if (randomPosition == 1) {
						line.spriteX = (float)position;
					}
					else if (randomPosition == 0) {
						line.spriteX = (float)(-position);
					}
				}
				else
					line.id = -1;
				if (decorationId == biomSwapPoint) decorationId = oldIdDecoration;
				lines.push_back(line);
			}
			getline(myfile, input);
		}


		myfile.close();
	}

	myfile.close();

	//StartSign
	lines[startSignPos].id = startSign;
	lines[startSignPos].spriteX = 0;

	N = lines.size();
	return true;
}

ModuleSceneMapAfrica::~ModuleSceneMapAfrica()
{}
