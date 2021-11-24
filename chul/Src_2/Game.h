#ifndef GAME_H
#define GAME_H 

#include "defs.h"
#include "TextureManager.h"
#include "Map.h"
#include "Vector2D.h"


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
};

#endif