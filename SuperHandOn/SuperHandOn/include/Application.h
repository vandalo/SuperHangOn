#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <list>
#include "Globals.h"
#include "Module.h"
#include <time.h>

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleParticles;
class ModuleFont;


// Game modules ---
class ModulePlayer;
class ModuleSceneIntro;
class ModuleSceneMenuOne;
class ModuleSceneWorld;
class ModuleSceneMusic;
class ModuleSceneMapAfrica;
class ModuleEnemy;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleFont* font;
	ModuleCollision* collision;
	ModuleParticles* particles;

	// Game modules ---
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModuleSceneMenuOne* scene_menu_one;
	ModuleSceneWorld* scene_menu_world;
	ModuleSceneMusic* scene_menu_music;
	ModuleSceneMapAfrica* scene_menu_africa;

	ModuleEnemy* enemy;

	// Fonts
	unsigned int menusFont;
	unsigned int numericFontYellow;
	unsigned int numericFontWhite;
	unsigned int numericFontRed;
	unsigned int numericFontGreen;
	unsigned int musicChosed = 0;

	// Music
	unsigned int fxLoadTrack;
	unsigned int fxSemaphorOne;
	unsigned int fxSemaphorFinish;

private:
	clock_t timer = 0;
	float deltaTime = 0;
	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_H__