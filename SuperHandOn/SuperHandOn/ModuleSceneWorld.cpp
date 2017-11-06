#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneWorld.h"
#include <string>

ModuleSceneWorld::ModuleSceneWorld(bool active) : Module(active)
{
	continentSelected = AFRICA;
	timer_fast = 0;
	timer_slow = 0;
	time_out = 12;
	//background color
	background.x = 0;
	background.y = 0;
	background.w = 640;
	background.h = 480;

	//Continets
	backgroundAfrica = { 584, 2, 110, 116 };
	backgroundEurope = { 694, 6, 118, 104 };
	backgroundAsia = { 784, 106, 240, 276 };
	backgroundAmerica = { 564 , 120, 196, 260 };

	//Continent texts
	textEurope = { 428, 40, 147, 36 };
	textAfrica = { 281, 0, 147, 39 };
	textAsia = { 281, 40, 147, 39 };
	textAmerica = { 426, 0, 149, 40 };

	americanX = SCREEN_WIDTH / 20;
	americanY = SCREEN_HEIGHT / 2 - backgroundAmerica.h / 2;
	asiaX = SCREEN_WIDTH - SCREEN_WIDTH / 20 - backgroundAsia.w;
	asiaY = SCREEN_HEIGHT / 2 - backgroundAsia.h / 2;
	europeX = SCREEN_WIDTH - SCREEN_WIDTH / 20 - backgroundEurope.w - backgroundAsia.w + 37;
	europeY = SCREEN_HEIGHT / 2 - backgroundEurope.h / 2 - 54;
	africaX = SCREEN_WIDTH - SCREEN_WIDTH / 20 - backgroundAfrica.w - backgroundAsia.w + 37;
	africaY = SCREEN_HEIGHT / 2 - backgroundAfrica.h / 2 + 48;

	//Text
	textSelectClass = { 3, 3, 278, 21 };
	textPushStart = { 3, 26, 278, 20 };
	
}

ModuleSceneWorld::~ModuleSceneWorld()
{}

// Load assets
bool ModuleSceneWorld::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("sprites/miscellaneous.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	App->audio->PlayFx(App->selectYourClass, true);
	App->musicPlaying = App->selectYourClass;
	return true;
}

// UnLoad assets
bool ModuleSceneWorld::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);
	current_animation = nullptr;

	return true;
}

// Update: draw background
update_status ModuleSceneWorld::Update()
{
	timer_fast++;
	timer_slow++;

	App->renderer->DrawQuad(background, (Uint8)160, (Uint8)192, (Uint8)224, (Uint8)255, false);
	//Continents
	if(continentSelected == AMERICA && timer_fast < INTERMITENT_FAST || continentSelected != AMERICA)
		App->renderer->Blit(graphics, americanX, americanY, &backgroundAmerica, 0.0f);
	if (continentSelected == ASIA && timer_fast < INTERMITENT_FAST || continentSelected != ASIA)
		App->renderer->Blit(graphics, asiaX, asiaY, &backgroundAsia, 0.0f);
	if (continentSelected == EUROPE && timer_fast < INTERMITENT_FAST || continentSelected != EUROPE)
		App->renderer->Blit(graphics, europeX, europeY, &backgroundEurope, 0.0f);
	if (continentSelected == AFRICA && timer_fast < INTERMITENT_FAST || continentSelected != AFRICA)
		App->renderer->Blit(graphics, africaX, africaY, &backgroundAfrica, 0.0f);

	//textContinents
	App->renderer->Blit(graphics, americanX + 40, americanY + 60, &textAmerica, 0.0f);
	App->renderer->Blit(graphics, asiaX + 50, asiaY + 35, &textAsia, 0.0f);
	App->renderer->Blit(graphics, europeX, europeY + 30, &textEurope, 0.0f);
	App->renderer->Blit(graphics, africaX, africaY + 30, &textAfrica, 0.0f);

	if(timer_slow < INTERMITENT_SLOW)
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - textPushStart.w / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 6, &textPushStart, 0.0f);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - textSelectClass.w / 2, SCREEN_HEIGHT / 6, &textSelectClass, 0.0f);

	App->renderer->Print(App->menusFont, to_string(time_out).c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);

	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || logo.Finished()))
	{
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && App->fade->isFading() == false) {
		continentSelected++;
		if (continentSelected > 3) continentSelected = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN && App->fade->isFading() == false) {
		if (continentSelected == 0) continentSelected = 3;
		else continentSelected--;
	}

	if (time_out == 1 || (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->fade->isFading() == false)) {
		App->fade->FadeToBlack((Module*)App->scene_menu_music, this);
	}

	if (timer_slow == INTERMITENT_SLOW && time_out > 0) time_out--;

	if (timer_fast > INTERMITENT_FAST * 2) timer_fast = 0;
	if (timer_slow > INTERMITENT_SLOW * 2) timer_slow = 0;

	return UPDATE_CONTINUE;
}