#include "Game.h"
#include "ECS/Components.h"

//git init test~~

Game::Game()
{}
Game::~Game()
{}

Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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

	player.addComponent<TransformComponent>(2); //default  = (x0,y0) = (0.0f,0.0f)
	player.addComponent<SpriteComponent>("./assets/warrior.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player"); //tag

	wall.addComponent<TransformComponent>(300.0f,300.0f,300,20,1); // x,y,w,h,sc
	wall.addComponent<SpriteComponent>("./assets/dirt.png"); //src path
	wall.addComponent<ColliderComponent>("wall"); //tag
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

	if(Collision::AABB(player.getComponent<ColliderComponent>().collider,
						wall.getComponent<ColliderComponent>().collider)) //player와 wall의 충돌발생 시
	{
		player.getComponent<TransformComponent>().scale = 1;  //이렇게 하면 플레이어 크기가 반토막남 2->1
		std::cout << "Wall Hit!!" << std::endl;
	}

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