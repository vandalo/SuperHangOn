#ifndef __ModuleSceneMenuOne_H__
#define __ModuleSceneMenuOne_H__

#include "Module.h"
#include "Animation.h"


enum PointerPosition {
	OPTION_ONE,
	OPTION_TWO
};

enum State {
	STATE_ONE,
	STATE_TWO
};

class ModuleSceneMenuOne : public Module
{
public:
	ModuleSceneMenuOne(bool active = true);
	~ModuleSceneMenuOne();

	bool Start();
	update_status Update(float deltaTime);
	bool CleanUp();

public:

	SDL_Texture* graphicsHangOnTitle = nullptr;
	Animation logo;

	SDL_Texture* graphicsSegaLogo = nullptr;
	Animation segaLogo;
	
	SDL_Texture* graphicsOptions = nullptr;
	SDL_Rect backgroundOptions;
	SDL_Rect backgroundOptionsTwo;
	SDL_Rect copyRightSaga;
	Animation pointer;
	PointerPosition pointerPosition;
	State state;
};

#endif // __ModuleSceneMenuOne_H__