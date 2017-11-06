#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

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

	// Musics
	unsigned int selectYourClass;
	unsigned int outrideaCrisis;
	unsigned int sprinter;
	unsigned int winningRun;
	unsigned int hardRoad;
	unsigned int finished;
	unsigned int enterYourName;
	unsigned int winnerShopBGM;

	// Fonts
	unsigned int menusFont;

	unsigned int musicPlaying;

private:

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__