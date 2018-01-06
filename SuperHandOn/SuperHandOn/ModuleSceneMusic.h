#ifndef __ModuleSceneMusic_H__
#define __ModuleSceneMusic_H__

#include "Module.h"
#include "Animation.h"

class ModuleSceneMusic : public Module
{
public:
	ModuleSceneMusic(bool active = true);
	~ModuleSceneMusic();

	bool Start();
	update_status Update(const float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	unsigned int musicSelected;
	SDL_Rect background;
	SDL_Rect backgroundMusic;
	SDL_Rect textPushStart;
	SDL_Rect textSelectMusic;
	SDL_Rect backgroundMusicSelected;
	float timer_fast, timer_slow;

private:
	bool swaped = false;
	float time_out;
};

#endif // __ModuleSceneMusic_H__