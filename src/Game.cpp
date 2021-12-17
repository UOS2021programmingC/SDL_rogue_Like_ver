// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
//업데이트 목록
// 백그라운드 설정 및, 한번 클리어 시 백그라운드 변경 -설정 완료
// 맵 변경을 위한 포탈 설정 중 - 설정 완료
//포탈 충돌 감지 기능 추가 중 - 

#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
#include "defs.h"
#include "BGSpriteComponent.h"
#include "Portal.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
,numEnemy(0)
,mDifficulty(1.0f)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("The road to A", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	Random::Init();
	SetPortalState(false);
	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	//다 죽고, 포탈이 없을때
	if (numEnemy <= 0 && mActivePortal ==false)
	{
		new Portal(this);
		// temp->SetPosition(Vector2(512.0f, 384.0f));
		// // Create the "far back" background
		// BGSpriteComponent* bg = new BGSpriteComponent(temp);
		// bg->SetScreenSize(Vector2(1024.0f, 768.0f));
		// std::vector<SDL_Texture*> bgtexs = {
		// 	GetTexture("Assets/Farback02.png"),
		// 	GetTexture("Assets/Farback02.png")
		// };
		// bg->SetBGTextures(bgtexs);
		// bg->SetScrollSpeed(100.0f);
		// // Create the closer background
		// bg = new BGSpriteComponent(temp, 50);
		// bg->SetScreenSize(Vector2(1024.0f, 768.0f));
		// bgtexs = {
		// 	GetTexture("Assets/Stars.png")
		// 	// ,GetTexture("Assets/Stars.png")
		// };
		// bg->SetBGTextures(bgtexs);
		// bg->SetScrollSpeed(100.0f);
	}
	//포탈활성화
	if (mActivePortal == true)
	{
		mDifficulty *= 1.5f;
		int numAsteroids = Random::GetIntRange((int)(3 + mDifficulty), (int)(10 + mDifficulty));
		numEnemy += numAsteroids;
		//백그라운드 변경+재소환
		Actor *temp = new Actor(this);
		SetBackGround(temp, 1);
		for (int i = 0; i < numAsteroids; i++)
		{
			new Asteroid(this);
		}
		
		SetPortalState(false);
	}
	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors) 
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			switch(actor->GetName())
			{
				case Actor::Player :
					mIsRunning = false; //게임종료
					break;
				case Actor::Enemy :
					numEnemy--; //적카운팅 감소
					break;
				case Actor::RESETTER : 
					SetPortalState(true);
				break;
			}
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);
	
	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.0f, 384.0f));
	mShip->SetRotation(Math::PiOver2);

	// Create asteroids
	int numAsteroids = Random::GetIntRange(3,7);
	numEnemy += numAsteroids;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}

	//변경부분 백그라운드 추가 - 후속으로 스테이지 변경 시 백그라운드 변경 예정 - 완료
	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	SetBackGround(temp,1);	
}

/**
 * @brief Set the Back Ground object
 * 
 * @param tmp  Class Actor*
 * @param stage stage NUM
 */
void Game::SetBackGround(class Actor* tmp , int stage)
{
	tmp->SetPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent *bg = new BGSpriteComponent(tmp);
	BGSpriteComponent *bg2 = new BGSpriteComponent(tmp,50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bg2->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture *> bgtexs;
	std::vector<SDL_Texture *> bgtexs2;
	switch (stage)
	{
	case 1:
		bgtexs = {
			tmp->GetGame()->GetTexture("Assets/Farback01.png"),
			tmp->GetGame()->GetTexture("Assets/Farback02.png")};
		bgtexs2 = {
			tmp->GetGame()->GetTexture("Assets/Stars.png"),
			tmp->GetGame()->GetTexture("Assets/Stars.png")};
		break;
	case 2:
		bgtexs = {
			tmp->GetGame()->GetTexture("Assets/Farback01.png"),
			tmp->GetGame()->GetTexture("Assets/Farback02.png")};
		bgtexs2 = {
			tmp->GetGame()->GetTexture("Assets/Stars.png"),
			tmp->GetGame()->GetTexture("Assets/Stars.png")};
		break;
	}
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-50.0f);
	bg2->SetBGTextures(bgtexs2);
	bg2->SetScrollSpeed(-50.0f);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(),
		mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}
// 포탈 생성
// void Game::AddPortal(Portal* pot)
// {
// 	mPortal.emplace_back(pot);
// }
// //포탈 삭제
// void Game::RemovePortal(Portal* pot)
// {
// 	auto iter = std::find(mPortal.begin(),
// 		mPortal.end(), pot);
// 	if (iter != mPortal.end())
// 	{
// 		mPortal.erase(iter);
// 	}
// }


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
