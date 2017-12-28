#ifndef __ModuleSceneTrack_H__
#define __ModuleSceneTrack_H__

#include "Module.h"
#include "Animation.h"

class Line;
class ModuleEnemy;

struct Decoration {
	float minX;
	float maxX;

	SDL_Rect rect;
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

class ModuleSceneTrack : public Module
{

public:
	ModuleSceneTrack(bool active = true);
	~ModuleSceneTrack();

	bool Start();
	update_status Update(float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* decorationSprite = nullptr;
	SDL_Texture* gui = nullptr;

	SDL_Rect sempahorYellow;
	SDL_Rect sempahorBlue;
	//SDL_Rect startSign;
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

	//SDL_Rect deadTree;

	SDL_Rect obejct;

	SDL_Rect road;
	SDL_Rect limit;
	SDL_Rect midLine;

	Color grass1;
	Color grass2;
	Color rumble1;
	Color rumble2;
	Color color_road;
	Color color_line;

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
	int checkSign;
	int goalSign;
	int people;

private:
	void PrintTrack(float deltaTime);
	void PrintGui();
	bool TrentToN(int n, int &res, float deltaTime, float &animationTime);

private:
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

	float acceleration = ACCELERATION;
	unsigned int sempahorState = 0;

	float mostAdvancedEnemyZ;
};

#endif // __ModuleSceneTrack_H__