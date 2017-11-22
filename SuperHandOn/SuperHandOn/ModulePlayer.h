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
	RIGHT_THREE
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update(float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation straight;
	Animation turnRightOne;
	Animation turnRightTwo;
	Animation turnRightThree;
	Animation turnLeftOne;
	Animation turnLeftTwo;
	Animation turnLeftThree;
	//Animation down;
	iPoint position;
	bool destroyed = false;

private:
	unsigned int state;
	float timer_movment;
};

#endif