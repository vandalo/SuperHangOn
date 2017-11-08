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
#include "ModulePlayer.h"

ModuleSceneMapAfrica::ModuleSceneMapAfrica(bool active) : Module(active)
{
	backgroundDesert = { 16, 60, 640, 480 };
	backgroundFrontDesert = { 669, 96, 623, 30 };

}

ModuleSceneMapAfrica::~ModuleSceneMapAfrica()
{}

// Load assets
bool ModuleSceneMapAfrica::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("sprites/backgrounds.png");
	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneMapAfrica::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);


	return true;
}


// Update: draw background
update_status ModuleSceneMapAfrica::Update(float deltaTime)
{

	App->renderer->Blit(graphics, 0, 0, &backgroundDesert, 0.0f);
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT / 2 + 7, &backgroundFrontDesert, .05f);
	App->renderer->Blit(graphics, 610, SCREEN_HEIGHT / 2 + 7, &backgroundFrontDesert, .05f);
	App->renderer->Blit(graphics, -610, SCREEN_HEIGHT / 2 + 7, &backgroundFrontDesert, .05f);

	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN))
	{
		
	}
	
	return UPDATE_CONTINUE;
}