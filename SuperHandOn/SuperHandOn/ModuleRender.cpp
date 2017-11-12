#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleFont.h"
#include "SDL/include/SDL.h"

#include "SDL_gfx/include/sdl2_gfxprimitives.h"

#pragma comment( lib, "SDL_gfx/libx86/SDL2_gfx.lib" )

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate(float deltaTime)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update(float deltaTime)
{
	// debug camera
	int speed = 1;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate(float deltaTime)
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool moveX, bool moveY)
{
	bool ret = true;
	SDL_Rect rect;
	if (moveX) rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	else  rect.x = (int)(camera.x * 0) + x * SCREEN_SIZE;
	if (moveY) rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;
	else rect.y = (int)(camera.y * 0) + y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::Print(unsigned int idFont, const char * text, int x, int y, float speed)
{
	bool ret = true;

	SDL_Rect leter;
	SDL_Rect position;
	Font font = App->font->fonts[idFont];

	position.x = x - (strlen(text) * font.width / 2) - font.width;
	position.y = y - (font.heigth / 2);
	for (int i = 0; text[i] != '\0'; i++) {
		int value = font.fontMap.find(text[i])->second;
		leter.h = font.heigth;
		leter.w = font.width;
		leter.x = value;
		leter.y = 0;
		position.w = leter.w;
		position.h = leter.h;
		position.x += font.width;
		if (SDL_RenderCopy(renderer, font.surface, &leter, &position) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawPoly(Color c, short x1, short y1, short w1, short x2, short y2, short w2)
{
	short s[4] = { x1 - w1, x2 - w2, x2 + w2, x1 + w1 };
	short t[4] = { y1, y2, y2, y1 };

	filledPolygonRGBA(renderer,
		s, t,
		4,
		c.r, c.g, c.b, c.a);
	return true;
}
