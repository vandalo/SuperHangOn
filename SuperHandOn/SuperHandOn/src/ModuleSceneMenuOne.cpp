#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMenuOne.h"

ModuleSceneMenuOne::ModuleSceneMenuOne(bool active) : Module(active)
{
	//width 640, height 185, numSprites 45 //rows of 3
	int j = 0;
	for (int i = 0; i < 45; i++) {
		if (i > 0 && i % 3 == 0) j++;
		logo.frames.push_back({ (i % 3) * 640,j * 185,640,182 });
	}
	j--;
	for (int i = 0; i < 3; i++) {
		logo.frames.push_back({ (i % 3) * 640,j * 185,640,182 });
	}
	logo.loop = false;
	logo.speed = 0.08f;

	//width 640, height 53, numSprites 15 //rows of 3
	j = 0;
	for (int i = 0; i < 15; i++) {
		if (i > 0 && i % 3 == 0) j++;
		segaLogo.frames.push_back({ (i % 3) * 640,j * 53,640,53 });
	}
	segaLogo.loop = true;
	segaLogo.speed = 0.1f;

	//Options (new game / password)
	backgroundOptions.x = 0;
	backgroundOptions.y = 0;
	backgroundOptions.w = 640;
	backgroundOptions.h = 48;

	//Options (ArcadeMode/ OriginalMode)
	backgroundOptionsTwo.x = 0;
	backgroundOptionsTwo.y = 84;
	backgroundOptionsTwo.w = 640;
	backgroundOptionsTwo.h = 48;

	//copyRightLogo
	copyRightSaga.x = 0;
	copyRightSaga.y = 48;
	copyRightSaga.w = 640;
	copyRightSaga.h = 20;

	//Pointer
	pointer.frames.push_back({ 0, 68, 16, 16 });
	pointer.frames.push_back({ 0, 48, 16, 16 });
	pointer.loop = true;
	pointer.speed = 0.05f;

	pointerPosition = OPTION_ONE;
	state = STATE_ONE;

}

ModuleSceneMenuOne::~ModuleSceneMenuOne()
{}

// Load assets
bool ModuleSceneMenuOne::Start()
{
	graphicsHangOnTitle = App->textures->Load("resources/sprites/superHangOnLogo.bmp");
	graphicsSegaLogo = App->textures->Load("resources/sprites/segaLogoMenuOne.bmp");
	graphicsOptions = App->textures->Load("resources/sprites/menuOneOptions.bmp");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneMenuOne::CleanUp()
{
	LOG("Unloading space scene");

	//App->textures->Unload(logo);

	return true;
}

// Update: draw background
update_status ModuleSceneMenuOne::Update(const float deltaTime)
{
	App->renderer->Blit(graphicsHangOnTitle, 0, logo.GetCurrentFrame().h / 2 - 30, &(logo.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphicsSegaLogo, 0, SCREEN_HEIGHT - segaLogo.GetCurrentFrame().h * 2, &(segaLogo.GetCurrentFrame()), 0.0f);

	if(state == STATE_ONE)
		App->renderer->Blit(graphicsOptions, 0, SCREEN_HEIGHT / 2 + backgroundOptions.h, &backgroundOptions, 0.0f);
	else
		App->renderer->Blit(graphicsOptions, 0, SCREEN_HEIGHT / 2 + backgroundOptions.h, &backgroundOptionsTwo, 0.0f);

	int incrementY = 0;
	if (pointerPosition == OPTION_TWO) incrementY = backgroundOptions.h / 2 + 8;
	int decrementX = 0;
	if (state == STATE_TWO) decrementX = 50;
	App->renderer->Blit(graphicsOptions, SCREEN_HEIGHT / 2 - 30 - decrementX, SCREEN_HEIGHT / 2 + backgroundOptions.h + incrementY, &(pointer.GetCurrentFrame()), 0.0f);

	App->renderer->Blit(graphicsOptions, 0, SCREEN_HEIGHT - copyRightSaga.h , &copyRightSaga, 0.0f);


	if ((App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) && App->fade->isFading() == false) {
		if (pointerPosition == OPTION_ONE) pointerPosition = OPTION_TWO;
		else pointerPosition = OPTION_ONE;
	}

	if (state == STATE_ONE  && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->fade->isFading() == false && pointerPosition == OPTION_ONE) {
		state = STATE_TWO;
	}
	else if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->fade->isFading() == false && pointerPosition == OPTION_ONE) {
		App->fade->FadeToBlack((Module*)App->scene_menu_world, this);
	}

	return UPDATE_CONTINUE;
}