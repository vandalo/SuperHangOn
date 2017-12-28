#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
//#include "ModuleParticles.h"
#include "ModuleRender.h"
//#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleSceneTrack.h"
//TMP
#include "ModuleSceneMapAfrica.h"


ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	timer_movment = 0;
	state = STRAIGHT;
	breaking = false;
	colision = NOT_FALLING;

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

	//BREAK
	// straight moto
	breakStraight.frames.push_back({ 992, 564, 66, 146 });
	breakStraight.frames.push_back({ 1068, 564, 66, 146 });
	breakStraight.loop = true;
	breakStraight.speed = 0.04f;
	
	// turn LeftOne
	breakTurnLeftThree.frames.push_back({ 1500, 600, 126, 110 });
	breakTurnLeftThree.frames.push_back({ 1630, 600, 126, 110 });
	breakTurnLeftThree.loop = true;
	breakTurnLeftThree.speed = 0.04f;

	// turn LeftTwo
	breakTurnLeftTwo.frames.push_back({ 1298, 584, 92, 126 });
	breakTurnLeftTwo.frames.push_back({ 1400, 584, 92, 126 });
	breakTurnLeftTwo.loop = true;
	breakTurnLeftTwo.speed = 0.04f;

	// turn LeftThree
	breakTurnLeftOne.frames.push_back({ 1146, 568, 72, 142 });
	breakTurnLeftOne.frames.push_back({ 1222, 568, 72, 142 });
	breakTurnLeftOne.loop = true;
	breakTurnLeftOne.speed = 0.04f;

	// turn RighttOne
	breakTurnRightOne.frames.push_back({ 1606, 726, 72, 142 });
	breakTurnRightOne.frames.push_back({ 1682, 726, 72, 142 });
	breakTurnRightOne.loop = true;
	breakTurnRightOne.speed = 0.04f;

	// turn RightTwo
	breakTurnRightTwo.frames.push_back({ 1408, 742, 92, 126 });
	breakTurnRightTwo.frames.push_back({ 1510, 742, 92, 126 });
	breakTurnRightTwo.loop = true;
	breakTurnRightTwo.speed = 0.04f;

	// turn RightThree
	breakTurnRightThree.frames.push_back({ 1144, 758, 126, 110 });
	breakTurnRightThree.frames.push_back({ 1274, 758, 126, 110 });
	breakTurnRightThree.loop = true;
	breakTurnRightThree.speed = 0.04f;
	
	//Particles
	outOfRoad.frames.push_back({ 1285,56,28,13 });
	outOfRoad.frames.push_back({ 1317,44,43,25 });
	outOfRoad.frames.push_back({ 1363,19,45,50 });
	outOfRoad.frames.push_back({ 1238,12,41,56 });
	outOfRoad.loop = true;
	outOfRoad.speed = 0.04f;


	//Turbo
	turboRightThree.frames.push_back({1141,900,126,110});
	turboRightThree.frames.push_back({ 1271, 900,126,110 });
	turboRightThree.loop = true;
	turboRightThree.speed = 0.04f;

	turboRightTwo.frames.push_back({ 1411,890,92,126 });
	turboRightTwo.frames.push_back({ 1513,890,92,126 });
	turboRightTwo.loop = true;
	turboRightTwo.speed = 0.04f;

	turboRightOne.frames.push_back({ 1608, 890, 72, 142 });
	turboRightOne.frames.push_back({ 1684, 890, 72, 142 });
	turboRightOne.loop = true;
	turboRightOne.speed = 0.04f;

	turboLeftThree.frames.push_back({ 1506,1091,126,110 });
	turboLeftThree.frames.push_back({ 1636, 1091,126,110 });
	turboLeftThree.loop = true;
	turboLeftThree.speed = 0.04f;

	turboLeftTwo.frames.push_back({ 1304,1075,92,126 });
	turboLeftTwo.frames.push_back({ 1406,1075,92,126 });
	turboLeftTwo.loop = true;
	turboLeftTwo.speed = 0.04f;

	turboLeftOne.frames.push_back({ 1152, 1059, 72, 142 });
	turboLeftOne.frames.push_back({ 1228, 1059, 72, 142 });
	turboLeftOne.loop = true;
	turboLeftOne.speed = 0.04f;

	turboStraight.frames.push_back({ 982, 870, 66, 146 });
	turboStraight.frames.push_back({ 1058, 870, 66, 146 });
	turboStraight.loop = true;
	turboStraight.speed = 0.04f;

	//falls
	slowFall.frames.push_back({ 0, 0, 220, 124 });
	slowFall.frames.push_back({ 220, 0, 220, 124 });
	slowFall.frames.push_back({ 440, 0, 220, 124 });
	slowFall.frames.push_back({ 660, 0, 220, 124 });
	slowFall.frames.push_back({ 880, 0, 220, 124 });
	slowFall.frames.push_back({ 1100, 0, 220, 124 });
	slowFall.frames.push_back({ 0, 124, 220, 124 });
	slowFall.frames.push_back({ 220, 124, 220, 124 });
	slowFall.frames.push_back({ 440, 124, 220, 124 });
	slowFall.frames.push_back({ 660, 124, 220, 124 });
	slowFall.frames.push_back({ 880, 124, 220, 124 });
	slowFall.frames.push_back({ 1100, 124, 220, 124 });
	slowFall.frames.push_back({ 0, 248, 220, 124 });
	slowFall.frames.push_back({ 0, 248, 220, 124 });
	slowFall.frames.push_back({ 0, 248, 220, 124 });
	slowFall.frames.push_back({ 0, 248, 220, 124 });
	slowFall.frames.push_back({ 0, 248, 220, 124 });
	slowFall.frames.push_back({ 0, 248, 220, 124 });
	slowFall.frames.push_back({ 99, 99, 0, 0 });
	slowFall.loop = false;
	slowFall.speed = 0.04f;

	fastFall.frames.push_back({ 0, 373, 171, 144 });
	fastFall.frames.push_back({ 171, 373, 171, 144 });
	fastFall.frames.push_back({ 342, 373, 171, 144 });
	fastFall.frames.push_back({ 513, 373, 171, 144 });
	fastFall.frames.push_back({ 684, 373, 171, 144 });
	fastFall.frames.push_back({ 855, 373, 171, 144 });
	fastFall.frames.push_back({ 1026, 373, 171, 144 });
	fastFall.frames.push_back({ 0, 517, 171, 144 });
	fastFall.frames.push_back({ 171, 517, 171, 144 });
	fastFall.frames.push_back({ 342, 517, 171, 144 });
	fastFall.frames.push_back({ 513, 517, 171, 144 });
	fastFall.frames.push_back({ 513, 517, 171, 144 });
	fastFall.frames.push_back({ 513, 517, 171, 144 });
	fastFall.frames.push_back({ 513, 517, 171, 144 });
	fastFall.frames.push_back({ 513, 517, 171, 144 });
	fastFall.frames.push_back({ 513, 517, 171, 144 });
	fastFall.frames.push_back({ 99, 99, 0, 0 });
	fastFall.loop = false;
	fastFall.speed = 0.04f;

	isOutofRoad = false;
	turbo = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("sprites/miscellaneous.png");
	graphicsFalls = App->textures->Load("sprites/falls.png");
	destroyed = false;
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT;

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
	if (colision == COLLISIONED || colision == FALLING) {
		if(App->scene_menu_africa->speed > 200 && colision == COLLISIONED) {
			current_animation = &fastFall;
		}
		else if (colision == COLLISIONED) current_animation = &slowFall;
		if (colision == COLLISIONED) current_animation->Reset();
		colision = FALLING;
		App->scene_menu_africa->speed = 0;
		fallDist = abs(App->scene_menu_africa->playerX);
	}
	else {
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			timer_movment += deltaTime;
			if (timer_movment > TIME_TO_SWAP) {
				if (state < RIGHT_THREE) {
					state++;
					timer_movment = 0;
				}
			}

		}
		else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			timer_movment += deltaTime;
			if (timer_movment > TIME_TO_SWAP) {
				if (state > LEFT_THREE) {
					state--;
					timer_movment = 0;
				}
			}

		}
		else {
			if (state != STRAIGHT) {
				timer_movment += deltaTime;
				if (timer_movment > TIME_TO_SWAP) {
					if (state < STRAIGHT) state++;
					else if (state > STRAIGHT) state--;
					timer_movment = 0;
				}
			}
		}

		switch (state) {
		case LEFT_ONE:
			if (breaking) current_animation = &breakTurnLeftOne;
			else if (turbo) current_animation = &turboLeftOne;
			else current_animation = &turnLeftOne;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2 + current_animation->GetCurrentFrame().w - outOfRoad.GetCurrentFrame().w / 2;
			break;
		case LEFT_TWO:
			if (breaking) current_animation = &breakTurnLeftTwo;
			else if (turbo) current_animation = &turboLeftTwo;
			else current_animation = &turnLeftTwo;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2 + current_animation->GetCurrentFrame().w - outOfRoad.GetCurrentFrame().w / 2;
			break;
		case LEFT_THREE:
			if (breaking) current_animation = &breakTurnLeftThree;
			else if (turbo) current_animation = &turboLeftThree;
			else current_animation = &turnLeftThree;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2 + current_animation->GetCurrentFrame().w - outOfRoad.GetCurrentFrame().w / 2;
			break;
		case STRAIGHT:
			if (breaking) current_animation = &breakStraight;
			else if (turbo) current_animation = &turboStraight;
			else current_animation = &straight;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2 + current_animation->GetCurrentFrame().w / 2 - outOfRoad.GetCurrentFrame().w / 2;
			break;
		case RIGHT_ONE:
			if (breaking) current_animation = &breakTurnRightOne;
			else if (turbo) current_animation = &turboRightOne;
			else current_animation = &turnRightOne;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2;
			break;
		case RIGHT_TWO:
			if (breaking) current_animation = &breakTurnRightTwo;
			else if (turbo) current_animation = &turboRightTwo;
			else current_animation = &turnRightTwo;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2;
			break;
		case RIGHT_THREE:
			if (breaking) current_animation = &breakTurnRightThree;
			else if (turbo) current_animation = &turboRightThree;
			else current_animation = &turnRightThree;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2;
			break;
		default:
			if (breaking) current_animation = &breakStraight;
			else current_animation = &straight;
			xParticle = position.x - current_animation->GetCurrentFrame().w / 2 + current_animation->GetCurrentFrame().w / 2 - outOfRoad.GetCurrentFrame().w / 2;
			break;
		}
	}
	if (destroyed == false)
		if (colision == FALLING) {
			App->renderer->Blit(graphicsFalls, position.x - (current_animation->GetCurrentFrame().w / 2) * 2, position.y - (current_animation->GetCurrentFrame().h) * 2, &(current_animation->GetCurrentFrame()), 0.f, false, false, current_animation->GetCurrentFrame().w * 2, current_animation->GetCurrentFrame().h * 2);
			if (current_animation->Finished()) {
				if(App->scene_menu_africa->playerX > 0)
					App->scene_menu_africa->playerX -= (fallDist / RECOVERY_MOVMENT) * deltaTime * 100;
				else if (App->scene_menu_africa->playerX < 0)
					App->scene_menu_africa->playerX += (fallDist / RECOVERY_MOVMENT) * deltaTime * 100;

				if (App->scene_menu_africa->playerX < 0.3 && App->scene_menu_africa->playerX > 0.0 || App->scene_menu_africa->playerX > -0.3  && App->scene_menu_africa->playerX < 0.0 || App->scene_menu_africa->playerX == 0.0) {
					App->scene_menu_africa->playerX = 0;
					App->scene_menu_africa->run = true;
					colision = NOT_FALLING;
					state = STRAIGHT;
				}
			}
		}
		else {
			App->renderer->Blit(graphics, position.x - current_animation->GetCurrentFrame().w / 2, position.y - current_animation->GetCurrentFrame().h, &(current_animation->GetCurrentFrame()), 0.f);
			if (isOutofRoad) App->renderer->Blit(graphics, xParticle, SCREEN_HEIGHT - outOfRoad.GetCurrentFrame().h, &outOfRoad.GetCurrentFrame(), 0.f);
		}
	return UPDATE_CONTINUE;
}
