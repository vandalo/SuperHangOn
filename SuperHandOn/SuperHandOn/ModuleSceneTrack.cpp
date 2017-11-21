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
	//startSign = 

	sempahor.frames.push_back({ 12, 265, 62, 142 });
	sempahor.frames.push_back({ 84, 265, 62, 142 });
	sempahor.frames.push_back({ 157, 265, 62, 142 });
	sempahor.frames.push_back({ 225, 265, 62, 142 });
	sempahor.loop = false;
	sempahor.speed = 0.01f;

	maxPuntuation = 6514651;
	stage = 1;
	time = 60;
	score = 0;
	speed = 200;

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
	dec_startSign->rect = { 7, 2, 627, 207 };
	decoration.push_back(dec_startSign);
	startSign = decoration.size() - 1;

	Decoration*dec_enemyOne = new Decoration();
	dec_enemyOne->maxX = 0;
	dec_enemyOne->minX = 0;
	dec_enemyOne->rect = { 181, 559, 66, 146 };
	decoration.push_back(dec_enemyOne);
	enemyOne = decoration.size() - 1;

	Enemy* enemy = new Enemy();
	enemy->color = GREEN;
	enemy->level = 1;
	enemy->posStopSprint = 1000;
	enemy->posZ = 12;
	enemy->posX = -0.5;
	enemys.push_back(enemy);

	Enemy* enemy2 = new Enemy();
	enemy2->color = GREEN;
	enemy2->level = 1;
	enemy2->posStopSprint = 1000;
	enemy2->posZ = 12;
	enemy2->posX = 0.2;
	enemys.push_back(enemy2);

	Enemy* enemy3 = new Enemy();
	enemy3->color = YELLOW;
	enemy3->level = 1;
	enemy3->posStopSprint = 1000;
	enemy3->posZ = 13;
	enemy3->posX = -0.1;
	enemys.push_back(enemy3);

	Enemy* enemy4 = new Enemy();
	enemy4->color = YELLOW;
	enemy4->level = 1;
	enemy4->posStopSprint = 1000;
	enemy4->posZ = 11;
	enemy4->posX = -0.8;
	enemys.push_back(enemy4);

	Enemy* enemy5 = new Enemy();
	enemy5->color = YELLOW;
	enemy5->level = 1;
	enemy5->posStopSprint = 1000;
	enemy5->posZ = 11;
	enemy5->posX = 0.5;
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

void ModuleSceneTrack::PrintTrack()
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

	//Draw Enemys
	for (int n = 0; n < enemys.size(); n++) {
		if (enemys[n]->posZ > startPos) {
			float enemysCurve = lines[(int)(enemys[n]->posZ) % N].curve;
			switch (enemys[n]->color) {
			case YELLOW:
				break;
			case GREEN:
				break;
			}
			lines[(int)(enemys[n]->posZ) % N].DrawObject(decoration[enemyOne]->rect, gui, enemys[n]->posX);
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
	//pos += 400;

	//Updates enemys position depends on the level
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->posZ += 390 / SEGL;
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
	
	
	PrintTrack();
	
	//DrawDecoration
	//App->renderer->Blit(decoration, 5, SCREEN_HEIGHT / 2  - 60, &startSign, 0.f);
	//App->renderer->Blit(decoration,  35, SCREEN_HEIGHT / 2 + 10, &sempahor.GetCurrentFrame(), 0.f);

	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN))
	{

	}

	time -= deltaTime;
	if (time < 0) time = 0;
	//Print GUI

	PrintGui();

	

	return UPDATE_CONTINUE;
}