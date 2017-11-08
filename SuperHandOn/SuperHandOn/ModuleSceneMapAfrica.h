#ifndef __ModuleSceneMapAfrica_H__
#define __ModuleSceneMapAfrica_H__

#include "Module.h"
#include "Animation.h"

class ModuleSceneMapAfrica : public Module
{

public:
	ModuleSceneMapAfrica(bool active = true);
	~ModuleSceneMapAfrica();

	bool Start();
	update_status Update(float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect backgroundDesert;
	SDL_Rect backgroundFrontDesert;
	uint fx = 0;

	SDL_Rect background1;
	SDL_Rect background2;
	SDL_Rect background3;

};

#endif // __ModuleSceneMapAfrica_H__