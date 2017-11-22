#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneTrack.h"
#include "ModulePlayer.h"
#include "Line.h"
#include <string>

ModuleSceneTrack::ModuleSceneTrack(bool active) : Module(active)
{
	sempahorYellow = { 463,250,75,32 };
	sempahorBlue = { 463,283,75,32 };

	maxPuntuation = 6514651;
	stage = 1;
	time = 60;
	score = 0;
	speed = 200;
	startTime = 0;

	backgroundTop = {33, 437, 62, 25};
	backgroundTime = { 97, 437, 76, 26 };
	backgroundScore = { 175, 437, 98, 26 };
	backgroundStage = { 275, 421, 83, 18 };
	backgroundStageProces = { 33, 467, 226, 18 };
	backgroundCourse = { 409, 421, 98, 18 };
	backgroundSpeed = { 275, 441, 82, 18 };
	backgroundKm = { 367, 441, 34, 18 };
	pos = 300000;

	Decoration*dec_tree = new Decoration();
	dec_tree->maxX = 4;
	dec_tree->minX = 2.5;
	dec_tree->rect = { 649, 0, 138, 209 };
	decoration.push_back(dec_tree);
	deadTree = decoration.size() - 1;

	Decoration*dec_startSign = new Decoration();
	dec_startSign->maxX = 0;
	dec_startSign->minX = 0;
	dec_startSign->rect = { 17, 426, 834, 278 };
	decoration.push_back(dec_startSign);
	startSign = decoration.size() - 1;

	/*Decoration*dec_startSempahor = new Decoration();
	dec_startSempahor->maxX = -1;
	dec_startSempahor->minX = -1;
	dec_startSempahor->rect = { 323, 234, 99, 174 };
	decoration.push_back(dec_startSempahor);
	decSemaphor = decoration.size() - 1;*/

	//Animation of IA
	//Green
	greenZero.frames.push_back({ 689,915,128,110 });
	greenZero.frames.push_back({ 819,915,128,110 });
	greenZero.loop = true;
	greenZero.speed = 0.04f;

	greenOne.frames.push_back({ 589,899,92,126 });
	greenOne.frames.push_back({ 487,899,92,126 });
	greenOne.loop = true;
	greenOne.speed = 0.04f;

	greenTwo.frames.push_back({ 411,889,72,136 });
	greenTwo.frames.push_back({ 335,889,72,136 });
	greenTwo.loop = true;
	greenTwo.speed = 0.04f;

	greenThree.frames.push_back({ 257,879,66,146 });
	greenThree.frames.push_back({ 181,879,66,146 });
	greenThree.loop = true;
	greenThree.speed = 0.04f;

	greenFour.frames.push_back({ 859,1215,72,142 });
	greenFour.frames.push_back({ 783,1215,72,142 });
	greenFour.loop = true;
	greenFour.speed = 0.04f;

	greenFive.frames.push_back({ 687,1231,92,126 });
	greenFive.frames.push_back({ 585,1231,92,126 });
	greenFive.loop = true;
	greenFive.speed = 0.04f;

	greenSix.frames.push_back({ 451,1247,126,110 });
	greenSix.frames.push_back({ 321,1247,126,110 });
	greenSix.loop = true;
	greenSix.speed = 0.04f;

	//Yellow
	yellowZero.frames.push_back({ 819,1075,126,110 });
	yellowZero.frames.push_back({ 689,1075,126,110 });
	yellowZero.loop = true;
	yellowZero.speed = 0.04f;

	yellowOne.frames.push_back({ 589,1059,92,126 });
	yellowOne.frames.push_back({ 487,1059,92,126 });
	yellowOne.loop = true;
	yellowOne.speed = 0.04f;

	yellowTwo.frames.push_back({ 411,1043,72,136 });
	yellowTwo.frames.push_back({ 335,1043,72,136 });
	yellowTwo.loop = true;
	yellowTwo.speed = 0.04f;

	yellowThree.frames.push_back({ 257,1039,66,146 });
	yellowThree.frames.push_back({ 181,1039,66,146 });
	yellowThree.loop = true;
	yellowThree.speed = 0.04f;

	yellowFour.frames.push_back({ 859,1375,72,142 });
	yellowFour.frames.push_back({ 859,1375,72,142 });
	yellowFour.loop = true;
	yellowFour.speed = 0.04f;

	yellowFive.frames.push_back({ 687,1390,92,126 });
	yellowFive.frames.push_back({ 585,1390,92,126 });
	yellowFive.loop = true;
	yellowFive.speed = 0.04f;

	yellowSix.frames.push_back({ 451,1407,126,110 });
	yellowSix.frames.push_back({ 321,1407,126,110 });
	yellowSix.loop = true;
	yellowSix.speed = 0.04f;

	Enemy* enemy = new Enemy();
	enemy->color = GREEN;
	enemy->level = 1;
	enemy->posStopSprint = 1000;
	enemy->posZ = 11;
	enemy->posX = -0.4;
	enemy->position = 3;
	enemy->current_animation = &greenThree;
	enemys.push_back(enemy);

	Enemy* enemy2 = new Enemy();
	enemy2->color = GREEN;
	enemy2->level = 1;
	enemy2->posStopSprint = 1000;
	enemy2->posZ = 11;
	enemy2->posX = 0.4;
	enemy2->position = 3;
	enemy2->current_animation = &greenThree;
	enemys.push_back(enemy2);

	Enemy* enemy3 = new Enemy();
	enemy3->color = YELLOW;
	enemy3->level = 1;
	enemy3->posStopSprint = 1000;
	enemy3->posZ = 13;
	enemy3->posX = 0;
	enemy3->position = 3;
	enemy3->current_animation = &yellowThree;
	enemys.push_back(enemy3);

	Enemy* enemy4 = new Enemy();
	enemy4->color = YELLOW;
	enemy4->level = 1;
	enemy4->posStopSprint = 1000;
	enemy4->posZ = 9;
	enemy4->posX = -0.7;
	enemy4->position = 3;
	enemy4->current_animation = &yellowThree;
	enemys.push_back(enemy4);

	Enemy* enemy5 = new Enemy();
	enemy5->color = YELLOW;
	enemy5->level = 1;
	enemy5->posStopSprint = 1000;
	enemy5->posZ = 9;
	enemy5->posX = 0.7;
	enemy5->position = 3;
	enemy5->current_animation = &yellowThree;
	enemys.push_back(enemy5);
}

ModuleSceneTrack::~ModuleSceneTrack()
{}

// Load assets
bool ModuleSceneTrack::Start()
{
	LOG("Loading space intro");
	//Load decorations

	graphics = App->textures->Load("sprites/backgrounds.png");

	//decor = App->textures->Load("sprites/decoration.png");
	gui = App->textures->Load("sprites/miscellaneous.png");

	//Load decoration sprites
	decorationSprite = App->textures->Load("sprites/decoration.png");

	//Gui fonts
	App->numericFontYellow = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18);
	App->numericFontWhite = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18, 18);
	App->numericFontRed = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18, 36);
	App->numericFontGreen = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18, 54);

	//ON DEBUG MODE
	App->menusFont = App->font->LoadMedia("fonts/font18x30.png", "9876543210", 18, 30);

	App->player->Enable();
	//App->enemy->Enable();
	return true;
}

// UnLoad assets
bool ModuleSceneTrack::CleanUp()
{
	LOG("Unloading space scene");
	App->textures->Unload(graphics);
	return true;
}

void ModuleSceneTrack::PrintTrack(float deltaTime)
{
	while (pos >= N * 200) pos -= N * SEGL;
	while (pos < 0) pos += N * SEGL;

	float x = 0, dx = 0;
	int startPos = pos / SEGL;
	int camH = (int)(1500 + lines[startPos].y);
	int maxy = HEIGHT;

	//Draw background
	App->renderer->Blit(graphics, 0, 0, &background, 0.0f);
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, 610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, -610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);

	for (int n = startPos; n < startPos + 300; n++) {
		Line &l = lines[n%N];
		l.project((int)(playerX - x), camH, pos - (n >= N ? N * 200 : 0));
		x += dx;
		dx += l.curve;

		l.clip = (float)maxy;
		if (l.Y >= maxy) continue;
		maxy = (int)(l.Y);

		Color grass = (n / 3) % 2 ? grass1 : grass2;
		Color rumble = (n / 3) % 2 ? rumble1 : rumble2;
		Color line = (n / 10) % 2 ? color_line : color_road;

		Line p = lines[(n - 1) % N]; //previous line

		//App->renderer->DrawPoly(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
		App->renderer->DrawPoly(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
		App->renderer->DrawPoly(rumble, (short)p.X, (short)p.Y, (short)(p.W*1.2), (short)l.X, (short)l.Y, (short)(l.W*1.2));
		App->renderer->DrawPoly(color_road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
		App->renderer->DrawPoly(line, (short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
	}

	//Draw Objects
	for (int n = startPos + 300; n > startPos; n--) {
		if (lines[n%N].id != -1)
			lines[n%N].DrawObject(decoration[lines[n%N].id]->rect, decorationSprite);
	}
	//Sempahor animation
	if (startTime != -1) {
		if (firstLoop) firstLoop = false;
		else {
			startTime += deltaTime;
			if (startTime < 4) {
				if (startTime < 3) App->renderer->Blit(decorationSprite, 14, SCREEN_HEIGHT / 2 + 19 + 62, &sempahorYellow, 0.f);
				else App->renderer->Blit(decorationSprite, 14, SCREEN_HEIGHT / 2 + 19 + 31, &sempahorYellow, 0.f);
			}
			if (startTime < 4) App->renderer->Blit(decorationSprite, 14, SCREEN_HEIGHT / 2 + 19, &sempahorBlue, 0.f);
			else if (startTime > 5) {
				startTime = -1;
				run = true;
				switch (App->musicChosed)
				{
				case OUTRIDE_A_CRISIS:
					App->musicChosed = OUTRIDE_A_CRISIS;
					App->audio->PlayMusic("music/2OutrideaCrisis.ogg", 0.f);
					break;
				case SPRINTER:
					App->musicChosed = SPRINTER;
					App->audio->PlayMusic("music/3Sprinter.ogg", 0.f);
					break;
				case WINNING_RUN:
					App->musicChosed = WINNING_RUN;
					App->audio->PlayMusic("music/4WinningRun.ogg", 0.f);
					break;
				case HARD_ROAD:
					App->musicChosed = HARD_ROAD;
					App->audio->PlayMusic("music/5HardRoad.ogg", 0.f);
					break;
				default:
					break;
				}
			}
		}
	}
	
	//Draw Enemys
	for (int n = 0; n < enemys.size(); n++) {
		if (enemys[n]->posZ > startPos) {
			float enemysCurve = lines[(int)(enemys[n]->posZ) % N].curve;
			bool animationChanged = false;
			if (enemysCurve < -3) {
				animationChanged = TrentToN(0, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			else if (enemysCurve < -1.5) {
				animationChanged = TrentToN(1, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			else if (enemysCurve < 0) {
				animationChanged = TrentToN(2, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			else if (enemysCurve > 3) {
				animationChanged = TrentToN(6, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			else if (enemysCurve > 1.5) {
				animationChanged = TrentToN(5, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			else if (enemysCurve > 0) {
				animationChanged = TrentToN(4, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			else {
				animationChanged = TrentToN(3, enemys[n]->position, deltaTime, enemys[n]->animationTime);
			}
			if (animationChanged) {
				switch (enemys[n]->position) {
				case 0:
					if(enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowZero;
					else enemys[n]->current_animation = &greenZero;
					break;
				case 1:
					if (enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowOne;
					else enemys[n]->current_animation = &greenOne;
					break;
				case 2:
					if (enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowTwo;
					else enemys[n]->current_animation = &greenTwo;
					break;
				case 3:
					if (enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowThree;
					else enemys[n]->current_animation = &greenThree;
					break;
				case 4:
					if (enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowFour;
					else enemys[n]->current_animation = &greenFour;
					break;
				case 5:
					if (enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowFive;
					else enemys[n]->current_animation = &greenFive;
					break;
				case 6:
					if (enemys[n]->color == YELLOW) enemys[n]->current_animation = &yellowSix;
					else enemys[n]->current_animation = &greenSix;
					break;
				default:
					break;
				}
			}
			lines[(int)(enemys[n]->posZ) % N].DrawObject(enemys[n]->current_animation->GetCurrentFrame(), gui, enemys[n]->posX);
		}
	}
}

void ModuleSceneTrack::PrintGui() {
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10), (SCREEN_HEIGHT / 20), &backgroundTop, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 2) - backgroundTime.w / 2, (SCREEN_HEIGHT / 20), &backgroundTime, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10) * 6, (SCREEN_HEIGHT / 20), &backgroundScore, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10), (SCREEN_HEIGHT / 20) * 2 + 8, &backgroundCourse, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10), (SCREEN_HEIGHT / 20) * 3, &backgroundStage, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 20), (SCREEN_HEIGHT / 20) * 4, &backgroundStageProces, 0.f);
	App->renderer->Blit(gui, (int)((SCREEN_WIDTH / 10) * 6.5), (int)((SCREEN_HEIGHT / 20) * 2 + 8), &backgroundSpeed, 0.f);
	App->renderer->Blit(gui, (int)((SCREEN_WIDTH / 10) * 8.5) + 16, (int)((SCREEN_HEIGHT / 20) * 2 + 8), &backgroundKm, 0.f);
	App->renderer->Blit(gui, (int)((SCREEN_WIDTH / 10) * 2.7), (int)((SCREEN_HEIGHT / 20) * 2 + 8), &backgroundTrackName, 0.f, false);

	//Text
	App->renderer->Print(App->numericFontRed, to_string((int)maxPuntuation).c_str(), (SCREEN_WIDTH / 10) + backgroundTop.w + 5, (SCREEN_HEIGHT / 20) + 4, 0.f, false);
	App->renderer->Print(App->numericFontGreen, to_string((int)score).c_str(), (SCREEN_WIDTH / 10) * 6 + backgroundScore.w + 5, (SCREEN_HEIGHT / 20) + 4, 0.f, false);
	if(speed < 280)
		App->renderer->Print(App->numericFontWhite, to_string((int)speed).c_str(), (int)((SCREEN_WIDTH / 10) * 6.5) + backgroundSpeed.w , (int)((SCREEN_HEIGHT / 20) * 2 + 8), 0.f, false);
	else
		App->renderer->Print(App->numericFontRed, to_string((int)speed).c_str(), (int)((SCREEN_WIDTH / 10) * 6.5) + backgroundSpeed.w , (int)((SCREEN_HEIGHT / 20) * 2 + 8), 0.f, false);
	App->renderer->Print(App->menusFont, to_string((int)time).c_str(), SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 20 * 3, 0.f);
	App->renderer->Print(App->numericFontWhite, to_string((int)stage).c_str(), (int)((SCREEN_WIDTH / 10) * 2.4), (int)((SCREEN_HEIGHT / 20) * 3), 0.f, false);
}


// Update: draw background
update_status ModuleSceneTrack::Update(float deltaTime)
{
	
	//Automove On debugmode
	//pos += 200;

	if (run) {
		//pos += 200;
		//Updates enemys position depends on the level
		for (int i = 0; i < enemys.size(); i++) {
			enemys[i]->posZ += 200 / SEGL;
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			pos += 400;
			score += 200;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			playerX += 70;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			playerX -= 70;
		}

		//Move player to compensate the force of the curve
		/*int startPos = pos / SEGL;
		float currentCurve = lines[startPos%N].curve;
		if (currentCurve > 3.5) playerX -= 60;
		else if (currentCurve > 2) playerX -= 45;
		else if (currentCurve > 1) playerX -= 25;
		else if (currentCurve > 0) playerX -= 15;
		else if (currentCurve < 0) {
		if (currentCurve > -1) playerX += 15;
		else if (currentCurve > 2) playerX += 25;
		else if (currentCurve > 3.5) playerX += 45;
		else playerX += 60;
		}*/
	}

	PrintTrack(deltaTime);

	time -= deltaTime;
	if (time < 0) time = 0;
	//Print GUI
	PrintGui();

	return UPDATE_CONTINUE;
}

bool ModuleSceneTrack::TrentToN(int n, int &res, float deltaTime, float &animationTime) {
	animationTime += deltaTime;
	bool ret = false;
	if (animationTime > TIME_TO_SWAP) {
		if (res > n) {
			res--;
			ret = true;
		}
		else if (res < n) {
			res++;
			ret = true;
		}
		if (ret) animationTime = 0;
	}
	return ret;
}