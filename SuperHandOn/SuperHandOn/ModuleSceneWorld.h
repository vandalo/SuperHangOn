#ifndef __ModuleSceneWorld_H__
#define __ModuleSceneWorld_H__

#include "Module.h"
#include "Animation.h"

enum ContinentSelect {
	EUROPE,
	AMERICA,
	ASIA,
	AFRICA
};


class ModuleSceneWorld : public Module
{
public:
	ModuleSceneWorld(bool active = true);
	~ModuleSceneWorld();

	bool Start();
	update_status Update(float deltaTime);
	bool CleanUp();

public:
	unsigned int continentSelected;
	float timer_fast, timer_slow;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	SDL_Rect background;
	SDL_Rect backgroundEurope;
	SDL_Rect backgroundAfrica;
	SDL_Rect backgroundAsia;
	SDL_Rect backgroundAmerica;

	SDL_Rect textEurope;
	SDL_Rect textAfrica;
	SDL_Rect textAsia;
	SDL_Rect textAmerica;

	SDL_Rect textPushStart;
	SDL_Rect textSelectClass;

	int americanX, americanY, asiaX, asiaY, europeX, europeY, africaX, africaY;
	Animation logo;

private:
	float time_out;
	bool swaped;
};

#endif // __ModuleSceneWorld_H__