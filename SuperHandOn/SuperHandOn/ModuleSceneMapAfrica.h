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
	Animation* current_animation = nullptr;
	Animation logo;
	uint fx = 0;
};

#endif // __ModuleSceneMapAfrica_H__