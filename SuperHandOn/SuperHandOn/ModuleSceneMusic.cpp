#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMusic.h"
#include <string>

ModuleSceneMusic::ModuleSceneMusic(bool active) : Module(active)
{
	timer_fast = 0;
	timer_slow = 0;
	musicSelected = 0;
	time_out = 12;

	background = { 0, 0, 640, 480};
	backgroundMusic = { 4, 54, 564, 217 };
	textPushStart = { 252, 2, 313, 22 };
	textSelectMusic = { 8, 3, 223, 24 };
	backgroundMusicSelected = { 4, 333, 564, 54 };
}

ModuleSceneMusic::~ModuleSceneMusic()
{}

// Load assets
bool ModuleSceneMusic::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("sprites/musicMenu.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;


	App->audio->PauseFx(App->musicPlaying);
	App->audio->PlayFx(App->outrideaCrisis, true);
	App->musicPlaying = App->outrideaCrisis;
	return true;
}

// UnLoad assets
bool ModuleSceneMusic::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneMusic::Update(float deltaTime)
{
	timer_fast += deltaTime;
	timer_slow += deltaTime;

	App->renderer->DrawQuad(background, (Uint8)224, (Uint8)160, (Uint8)0, (Uint8)255, false);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - backgroundMusic.w / 2, SCREEN_HEIGHT / 2 - backgroundMusic.h / 2, &backgroundMusic, 0.0f);

	if (timer_slow < INTERMITENT_SLOW) {
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - textPushStart.w / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 6 + 20, &textPushStart, 0.0f);
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - backgroundMusic.w / 2, SCREEN_HEIGHT / 2 - backgroundMusic.h / 2 + backgroundMusicSelected.h * musicSelected, &backgroundMusicSelected, 0.0f);
	}
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - textSelectMusic.w / 2, SCREEN_HEIGHT / 6, &textSelectMusic, 0.0f);

	App->renderer->Print(App->menusFont, to_string((int)time_out).c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 + 10);

	time_out -= deltaTime;

	if (timer_fast > INTERMITENT_FAST * 2) timer_fast = 0;
	if (timer_slow > INTERMITENT_SLOW * 2) timer_slow = 0;

	bool changedMusic = false;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN && App->fade->isFading() == false) {
		musicSelected++;
		if (musicSelected > 3) musicSelected = 0;
		changedMusic = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && App->fade->isFading() == false) {
		if (musicSelected == 0) musicSelected = 3;
		else musicSelected--;
		changedMusic = true;
	}

	if (changedMusic) {
		App->audio->PauseFx(App->musicPlaying);
		switch (musicSelected)
		{
		case OUTRIDE_A_CRISIS:
			App->audio->PlayFx(App->outrideaCrisis, true);
			App->musicPlaying = App->outrideaCrisis;
			break;
		case SPRINTER:
			App->audio->PlayFx(App->sprinter, true);
			App->musicPlaying = App->sprinter;
			break;
		case WINNING_RUN:
			App->audio->PlayFx(App->winningRun, true);
			App->musicPlaying = App->winningRun;
			break;
		case HARD_ROAD:
			App->audio->PlayFx(App->hardRoad, true);
			App->musicPlaying = App->hardRoad;
			break;
		default:
			break;
		}
	}

	return UPDATE_CONTINUE;
}