// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
// Updated by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------

#pragma once
#include "SDL2/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void SetBackGround(class Actor* tmp,int stage);

	SDL_Texture* GetTexture(const std::string& fileName);


	//포탈 추가
	// void AddPortal(class Portal* pot);
	// void RemovePortal(class Portal* pot);
	// std::vector<class Portal*>& GetPortal() { return mPortal; }
	// Game-specific (add/remove asteroid)
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }

	class Ship* GetShip() {return mShip; }
	float GetDiff() {return mDifficulty;}
	// class Portal* GetPortal() { return mPortal; }

	void SetPortalState(bool value) { mActivePortal = value; }
	int numEnemy;
	
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	class Ship *mShip; // Player's ship
	std::vector<class Asteroid*> mAsteroids;

	// class Portal *mPortal; 
	// // std::vector<class Portal*> mPortal;

	float mDifficulty;
	bool mActivePortal;
};
