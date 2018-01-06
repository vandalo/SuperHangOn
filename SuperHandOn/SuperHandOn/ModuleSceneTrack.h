#ifndef __ModuleSceneTrack_H__
#define __ModuleSceneTrack_H__

#include "Module.h"
#include "Animation.h"
#include <fstream>
#include <iostream>
#include <string>

class Line;
class ModuleEnemy;

struct Decoration {
	float minX;
	float maxX;

	SDL_Rect rect;
};

struct Bioma {
	Color grass1;
	Color grass2;
	Color rumble1;
	Color rumble2;
	Color color_road1;
	Color color_road2;
	Color color_line1;
	Color color_line2;
	Color sky;

	SDL_Rect background;
	SDL_Rect backgroundParalax;
};

struct Score {
	int score;
	int stage;
	string name;
	float time;
};

struct Enemy {
	float posZ;
	float posX;
	float animationTime = 0;
	int posStopSprint;
	int color;
	int speed;
	int position = 3;
	Animation* current_animation = nullptr;
};

enum EnemyColor {
	YELLOW,
	GREEN
};

enum FinishState {
	RUNNING,
	ANIMATION,
	BONUS,
	PUNTUATION
};

class ModuleSceneTrack : public Module
{

public:
	ModuleSceneTrack(bool active = true);
	~ModuleSceneTrack();

	bool Start();
	update_status Update(const float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* decorationSprite = nullptr;
	SDL_Texture* gui = nullptr;

	SDL_Rect sempahorYellow;
	SDL_Rect sempahorBlue;
	SDL_Rect background;
	SDL_Rect backgroundParalax;
	SDL_Rect backgroundTop;
	SDL_Rect backgroundTime;
	SDL_Rect backgroundScore;
	SDL_Rect backgroundStage;
	SDL_Rect backgroundStageProces;
	SDL_Rect backgroundCourse;
	SDL_Rect backgroundSpeed;
	SDL_Rect backgroundKm;
	SDL_Rect backgroundTrackName;
	SDL_Rect checkFill;
	SDL_Rect gameOver;
	SDL_Rect extendedPlay;
	SDL_Rect beginnerCourse;
	SDL_Rect obejct;

	/*SDL_Rect road;
	SDL_Rect limit;
	SDL_Rect midLine;*/

	Color grass1;
	Color grass2;
	Color rumble1;
	Color rumble2;
	Color color_road1;
	Color color_road2;
	Color color_line1;
	Color color_line2;
	Color sky;

	vector<Line> lines;
	

	int N = 0;
	int pos;
	int realPos = 0;
	int playerX;
	float speed = 0;
	bool run = false;

	vector<Decoration*> decoration;
	vector<Enemy*> enemys;
	//Array decoration item index
	int deadTree;
	int startSign;
	int signRight;
	int checkSign;
	int goalSign;
	int people;
	int signLeft;
	int tonnel;
	int bidalstone;
	int rock;
	int biomSwapPoint;
	int bushTree;
	int birdbird;
	int palmTree;
	int cactus;


private:
	void PrintTrack(float deltaTime);
	void PrintGui(float deltaTime);
	bool TrentToN(int n, int &res, float deltaTime, float &animationTime);
	void swapBioma(float deltaTime);
	string getTimeFromFloat(float time);
	void saveScore();

protected:
	Animation greenZero;
	Animation greenOne;
	Animation greenTwo;
	Animation greenThree;
	Animation greenFour;
	Animation greenFive;
	Animation greenSix;

	Animation yellowZero;
	Animation yellowOne;
	Animation yellowTwo;
	Animation yellowThree;
	Animation yellowFour;
	Animation yellowFive;
	Animation yellowSix;

	//Finish animation
	Animation finishPlayer;
	Enemy* finishAnimation;
	float goalPos;
	SDL_Rect finishPose;
	
	int maxPuntuation;
	int stage;
	float time;
	int score;
	int enemyOneZ;
	float startTime = 0;
	bool firstLoop = true;
	float delayCheckPoint;
	FinishState finished;
	float timeBonus = 5;
	float timeGameOver;

	float acceleration = ACCELERATION;
	unsigned int sempahorState = 0;

	float mostAdvancedEnemyZ;
	float checkTime;
	float lapTime;
	float lastLapTime;
	float totalTime;

	int currentBiomId;
	//BiomsIds
	int desertBiom;
	int mountainBiom;
	int desert2Biom;
	bool biomSwap;
	vector<int> biomsSequence;
	vector<Bioma*> bioms;
	float updateBiomTimer;
	float swapLeter;
	bool biomSwapBackgroundHelper;
	bool updatedPuntuation;
	int puntuationPoistion;
	int dictionariPosition;

	vector<float>stageTimeSaved;
	vector<Score> bestScores;
	vector<string> dictionari;
};

#endif // __ModuleSceneTrack_H__