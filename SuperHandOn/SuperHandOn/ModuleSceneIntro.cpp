#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"

ModuleSceneIntro::ModuleSceneIntro(bool active) : Module(active)
{
	//width 640, height 65, numSprites 48 //rows of 3
	int j = 0;
	for (int i = 0; i < 48; i++) {
		if (i % 3 == 0) j++;
		logo.frames.push_back({ (i%3) * 640,j*65,640,65 });
	}
	logo.loop = false;
	logo.speed = 0.2f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading space intro");

	App->fxLoadTrack = App->audio->LoadFx("music/fxLoadTrack.wav");
	App->fxSemaphorOne = App->audio->LoadFx("music/fxSempahorOne.wav");
	App->fxSemaphorFinish = App->audio->LoadFx("music/fxSempahorFinish.wav");
	graphics = App->textures->Load("sprites/segaLogo.bmp");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Load all fonts
	App->menusFont = App->font->LoadMedia("fonts/font18x30.png", "9876543210", 18, 30);

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);
	current_animation = nullptr;

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float deltaTime)
{
	current_animation = &logo;
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT*SCREEN_SIZE / 2 - current_animation->GetCurrentFrame().h/2, &(current_animation->GetCurrentFrame()));

	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || logo.Finished()))
	{
		App->fade->FadeToBlack((Module*)App->scene_menu_one, this);
	}

	return UPDATE_CONTINUE;
}