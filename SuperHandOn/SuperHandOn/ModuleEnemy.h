#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

class ModuleEnemy : public Module
{
public:
	ModuleEnemy(bool active = true);
	~ModuleEnemy();

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
	float time_to_swap = 0.5;
};

#endif