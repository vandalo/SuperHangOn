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
	swaped = false;

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

	graphics = App->textures->Load("resources/sprites/musicMenu.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	App->audio->PlayMusic("resources/music/2OutrideaCrisis.ogg", 0.f);
	musicSelected = 0;
	return true;
}

// UnLoad assets
bool ModuleSceneMusic::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);

	return true;
}

update_status ModuleSceneMusic::Update(const float deltaTime)
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
		switch (musicSelected)
		{
		case OUTRIDE_A_CRISIS:
			App->musicChosed = OUTRIDE_A_CRISIS;
			App->audio->PlayMusic("resources/music/2OutrideaCrisis.ogg", 0.f);
			break;
		case SPRINTER:
			App->musicChosed = SPRINTER;
			App->audio->PlayMusic("resources/music/3Sprinter.ogg", 0.f);
			break;
		case WINNING_RUN:
			App->musicChosed = WINNING_RUN;
			App->audio->PlayMusic("resources/music/4WinningRun.ogg", 0.f);
			break;
		case HARD_ROAD:
			App->musicChosed = HARD_ROAD;
			App->audio->PlayMusic("resources/music/5HardRoad.ogg", 0.f);
			break;
		default:
			break;
		}
	}
	if ((time_out < 1 && swaped == false) || (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->fade->isFading() == false)) {
		App->audio->MusicFadeOut();
		App->fade->FadeToBlack((Module*)App->scene_menu_africa, this);
		swaped = true;
	}

	return UPDATE_CONTINUE;
}