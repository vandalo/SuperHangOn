#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
//#include "ModuleParticles.h"
#include "ModuleRender.h"
//#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	// idle animation (just the ship)
	straight.frames.push_back({ 181, 559, 66, 146 });
	straight.frames.push_back({ 257, 559, 66, 146 });
	straight.loop = true;
	straight.speed = 0.04f;

	// move upwards
	//up.frames.push_back({ 100, 1, 32, 14 });
	//up.frames.push_back({ 132, 0, 32, 14 });
	//up.loop = false;
	//up.speed = 0.1f;

	// Move down
	//down.frames.push_back({ 33, 1, 32, 14 });
	//down.frames.push_back({ 0, 1, 32, 14 });
	//down.loop = false;
	//down.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("sprites/miscellaneous.png");

	destroyed = false;
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT - 20;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float deltaTime)
{
	/*int speed = 1;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{

	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
		current_animation = &idle;
		*/
	current_animation = &straight;
	if (destroyed == false)
		App->renderer->Blit(graphics, position.x - current_animation->GetCurrentFrame().w / 2, position.y - current_animation->GetCurrentFrame().h, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
