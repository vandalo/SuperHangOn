#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMapAfrica.h"

ModuleSceneMapAfrica::ModuleSceneMapAfrica(bool active) : Module(active)
{
	//width 640, height 65, numSprites 48 //rows of 3
	int j = 0;
	for (int i = 0; i < 48; i++) {
		if (i % 3 == 0) j++;
		logo.frames.push_back({ (i % 3) * 640,j * 65,640,65 });
	}
	logo.loop = false;
	logo.speed = 0.2f;
}

ModuleSceneMapAfrica::~ModuleSceneMapAfrica()
{}

// Load assets
bool ModuleSceneMapAfrica::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("sprites/segaLogo.bmp");

	return true;
}

// UnLoad assets
bool ModuleSceneMapAfrica::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);
	current_animation = nullptr;

	return true;
}

// Update: draw background
update_status ModuleSceneMapAfrica::Update(float deltaTime)
{
	current_animation = &logo;
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT*SCREEN_SIZE / 2 - current_animation->GetCurrentFrame().h / 2, &(current_animation->GetCurrentFrame()));

	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || logo.Finished()))
	{
		//App->fade->FadeToBlack((Module*)App->scene_menu_one, this);
	}

	return UPDATE_CONTINUE;
}