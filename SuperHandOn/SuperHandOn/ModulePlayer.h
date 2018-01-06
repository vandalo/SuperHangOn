#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

enum BikeState {
	LEFT_THREE,
	LEFT_TWO,
	LEFT_ONE,
	STRAIGHT,
	RIGHT_ONE,
	RIGHT_TWO,
	RIGHT_THREE,
};

enum Falls {
	COLLISIONED,
	NOT_FALLING,
	FALLING,
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update(const float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsFalls = nullptr;
	Animation* current_animation = nullptr;
	Animation straight;
	Animation turnRightOne;
	Animation turnRightTwo;
	Animation turnRightThree;
	Animation turnLeftOne;
	Animation turnLeftTwo;
	Animation turnLeftThree;

	Animation breakStraight;
	Animation breakTurnRightOne;
	Animation breakTurnRightTwo;
	Animation breakTurnRightThree;
	Animation breakTurnLeftOne;
	Animation breakTurnLeftTwo;
	Animation breakTurnLeftThree;
	//Animation down;
	iPoint position;
	bool destroyed = false;
	bool breaking;

	//Particles
	float xParticle;

	bool isOutofRoad;
	bool turbo;
	Falls colision;
	Animation outOfRoad;
	Animation turboRightThree;
	Animation turboLeftThree;
	Animation turboRightTwo;
	Animation turboLeftTwo;
	Animation turboRightOne;
	Animation turboLeftOne;
	Animation turboStraight;

	Animation fastFall;
	Animation slowFall;

private:
	unsigned int state;
	float timer_movment;
	float fallDist;
};

#endif