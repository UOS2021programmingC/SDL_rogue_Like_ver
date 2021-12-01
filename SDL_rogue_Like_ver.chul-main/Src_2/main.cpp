#include "Game.h"
#include "defs.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	Uint32 frameStart;
	int frameTime ;

	game = new Game();
	//화면 init
	game->init("GameWindow", WINDOW_WIDTH, WINDOW_HEIGHT, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if(FRAMEDELAY > frameTime){
			SDL_Delay(FRAMEDELAY - frameTime);
		}
	}

	game->clean();
	return 0;
}