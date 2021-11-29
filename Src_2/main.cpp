#include "Game.h"
#include "defs.h"
// #define EXIT

Game *game = nullptr;

#ifndef EXIT

volatile sig_atomic_t flag = 0;

void my_function(int sig)
{ // can be called asynchronously
  flag = 1; // set flag
}
#endif

int main(int argc, char *argv[])
{
	Uint32 frameStart;
	int frameTime ;

	signal (SIGINT, my_function); //강제종료

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

		if(flag){//ctrl+C입력시
			flag=0; 
			exit(1);
		} //강제종료
	}


// 	int main(){
//    // Register signal and signal handler
//    signal(SIGINT, signal_callback_handler);
//    while(true){
//       cout << "Program processing..." << endl;
//       sleep(1);
//    }
//    return EXIT_SUCCESS;
// }

	game->clean();
	return 0;
}