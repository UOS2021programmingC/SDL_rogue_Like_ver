#include "Game.h"
#include "ECS/Components.h"

Game::Game()
{}
Game::~Game()
{}

Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
SDL_Event Game::event;

auto& player(manager.addEntity());

static int mapArray[mapTile_row][mapTile_column];

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	map = new Map();
	map->LoadMap(1);

	//ECS implements 

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("./assets/warrior.png");
	player.addComponent<KeyboardController>();
	
	}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	//조건에따른 텍스터 교체 부분 사용법
/*
	

	if(player.getComponent<TransformComponent>().x()>100)
	{
		player.getComponent<SpriteComponent>().setTex("./assets/Enemy_purple_slime(left).png");
	}
*/
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}