#ifndef __ModuleSceneMusic_H__
#define __ModuleSceneMusic_H__

#include "Module.h"
#include "Animation.h"


enum MusicSelected {
	OUTRIDE_A_CRISIS,
	SPRINTER,
	WINNING_RUN,
	HARD_ROAD
};

class ModuleSceneMusic : public Module
{
public:
	ModuleSceneMusic(bool active = true);
	~ModuleSceneMusic();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	unsigned int musicSelected;
	SDL_Rect background;
	SDL_Rect backgroundMusic;
	SDL_Rect textPushStart;
	SDL_Rect textSelectMusic;
	SDL_Rect backgroundMusicSelected;
	unsigned int timer_fast, timer_slow;

};

#endif // __ModuleSceneMusic_H__