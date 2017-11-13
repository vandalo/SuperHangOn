#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
//#include "ModuleParticles.h"
#include "ModuleRender.h"
//#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"


ModuleEnemy::ModuleEnemy(bool active) : Module(active)
{
	timer_movment = 0;
	time_to_swap = 0.1f;
	state = 3;

	// straight moto
	straight.frames.push_back({ 181, 559, 66, 146 });
	straight.frames.push_back({ 257, 559, 66, 146 });
	straight.loop = true;
	straight.speed = 0.04f;

	// turn rightOne
	turnRightOne.frames.push_back({ 871, 721, 72, 142 });
	turnRightOne.frames.push_back({ 795, 721, 72, 142 });
	turnRightOne.loop = true;
	turnRightOne.speed = 0.04f;

	// turn rightTwo
	turnRightTwo.frames.push_back({ 699, 737, 92, 126 });
	turnRightTwo.frames.push_back({ 597, 737, 92, 126 });
	turnRightTwo.loop = true;
	turnRightTwo.speed = 0.04f;

	// turn rightThree
	turnRightThree.frames.push_back({ 463, 753, 126, 110 });
	turnRightThree.frames.push_back({ 333, 753, 126, 110 });
	turnRightThree.loop = true;
	turnRightThree.speed = 0.04f;

	// turn lefttOne
	turnLeftOne.frames.push_back({ 335, 563, 72, 142 });
	turnLeftOne.frames.push_back({ 411, 563, 72, 142 });
	turnLeftOne.loop = true;
	turnLeftOne.speed = 0.04f;

	// turn leftTwo
	turnLeftTwo.frames.push_back({ 487, 579, 92, 126 });
	turnLeftTwo.frames.push_back({ 589, 579, 92, 126 });
	turnLeftTwo.loop = true;
	turnLeftTwo.speed = 0.04f;

	// turn leftThree
	turnLeftThree.frames.push_back({ 689, 595, 126, 110 });
	turnLeftThree.frames.push_back({ 819, 595, 126, 110 });
	turnLeftThree.loop = true;
	turnLeftThree.speed = 0.04f;

}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("sprites/miscellaneous.png");

	destroyed = false;
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT - 20;

	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnemy::Update(float deltaTime)
{
	/*if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		timer_movment += deltaTime;
		if (timer_movment > time_to_swap) {
			if (state < RIGHT_THREE) {
				state++;
				timer_movment = 0;
			}
		}

	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		timer_movment += deltaTime;
		if (timer_movment > time_to_swap) {
			if (state > LEFT_THREE) {
				state--;
				timer_movment = 0;
			}
		}

	}
	else {
		if (state != STRAIGHT) {
			timer_movment += deltaTime;
			if (timer_movment > time_to_swap) {
				if (state < STRAIGHT) state++;
				else if (state > STRAIGHT) state--;
				timer_movment = 0;
			}
		}
	}

	switch (state) {
	case LEFT_ONE:
		current_animation = &turnLeftOne;
		break;
	case LEFT_TWO:
		current_animation = &turnLeftTwo;
		break;
	case LEFT_THREE:
		current_animation = &turnLeftThree;
		break;
	case STRAIGHT:
		current_animation = &straight;
		break;
	case RIGHT_ONE:
		current_animation = &turnRightOne;
		break;
	case RIGHT_TWO:
		current_animation = &turnRightTwo;
		break;
	case RIGHT_THREE:
		current_animation = &turnRightThree;
		break;
	default:
		current_animation = &straight;
		break;
	}
	*/
	current_animation = &straight;
	if (destroyed == false)
		App->renderer->Blit(graphics, SCREEN_HEIGHT / 2 - 30, position.y - current_animation->GetCurrentFrame().h, &(current_animation->GetCurrentFrame()), 0.f);

	return UPDATE_CONTINUE;
}
