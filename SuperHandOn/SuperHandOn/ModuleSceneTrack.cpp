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

ModuleSceneTrack::ModuleSceneTrack(bool active) : Module(active)
{
	startSign = { 7, 2, 627, 207};
}

ModuleSceneTrack::~ModuleSceneTrack()
{}

// Load assets
bool ModuleSceneTrack::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("sprites/backgrounds.png");
	decoration = App->textures->Load("sprites/decoration.png");
	App->player->Enable();

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

	while (pos >= N * 200) pos -= N * 200;
	while (pos < 0) pos += N * 200;

	float x = 0, dx = 0;
	int startPos = pos / 200;
	int camH = (int)(1500 + lines[startPos].y);
	int maxy = 480;

	for (int n = startPos; n < startPos + 300; n++) {
		Line &l = lines[n%N];
		l.project((int)(playerX - x), camH, pos - (n >= N ? N * 200 : 0));
		x += dx;
		dx += l.curve;

		if (l.Y >= maxy) continue;
		maxy = (int)(l.Y);

		Color grass = (n / 3) % 2 ? grass1 : grass2;
		Color rumble = (n / 3) % 2 ? rumble1 : rumble2;
		Color line = (n / 10) % 2 ? color_line : color_road;

		Line p;
		if (n == 0)
			p = lines[lines.size() - 1 % N]; //previous line
		else
			p = lines[(n - 1) % N]; //previous line

		App->renderer->DrawPoly(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
		App->renderer->DrawPoly(rumble, (short)p.X, (short)p.Y, (short)(p.W*1.2), (short)l.X, (short)l.Y, (short)(l.W*1.2));
		App->renderer->DrawPoly(color_road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
		App->renderer->DrawPoly(line, (short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
	}
}


// Update: draw background
update_status ModuleSceneTrack::Update(float deltaTime)
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		pos += 200;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		playerX += 20;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		playerX -= 20;
	}

	PrintTrack();


	//Draw background
	App->renderer->Blit(graphics, 0, 0, &background, 0.0f);
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, 610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, -610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);

	//DrawDecoration
	App->renderer->Blit(decoration, 5, SCREEN_HEIGHT / 2  - 60, &startSign, 0.f);


	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN))
	{

	}


	return UPDATE_CONTINUE;
}