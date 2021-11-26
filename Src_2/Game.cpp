#include "Game.h"
//순환 dependancy 조심 #include Game.h 하는 헤더파일은 여기에
#include "ECS/Components.h"
#include "Collision.h"

Game::Game()
{}
Game::~Game()
{}

Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

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

	tile0.addComponent<TileComponent>(200,200,32,32,0); //0=water

	tile1.addComponent<TileComponent>(250,250,32,32,1); //1=grass
	tile1.addComponent<ColliderComponent>("dirt");

	tile2.addComponent<TileComponent>(150,150,32,32,2); //2=dirt
	tile2.addComponent<ColliderComponent>("dirt"); 

	player.addComponent<TransformComponent>(SCALE*2); //default  = (x0,y0) = (0.0f,0.0f)
	player.addComponent<SpriteComponent>("./assets/warrior.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player"); //tag

	wall.addComponent<TransformComponent>(300.0f,300.0f,300,20,SCALE); // x,y,w,h,sc
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

	for (auto cc: colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(),*cc); //충돌 체크
	}
	
	if(Collision::AABB(player.getComponent<ColliderComponent>().collider,
						wall.getComponent<ColliderComponent>().collider)) //player와 wall의 충돌발생 시
	{
		player.getComponent<TransformComponent>().scale = SCALE;  //이렇게 하면 플레이어 크기가 반토막남 2scale->1scale
		/*
		*hit 발생시 속도변화
		*-1 = 튕김(bounce) 
		* 0 = 무한충돌(충돌에서 탈출못함, 속도0고정)
		*/
		player.getComponent<TransformComponent>().velocity*(-1); 
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