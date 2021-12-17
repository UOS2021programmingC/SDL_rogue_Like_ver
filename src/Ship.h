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
#include "Actor.h"
class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	class CircleComponent* GetCircle() { return mCircle; }
	class InputComponent* GetInputComponent() { return ic; }
	
	void SetLaserCool(float cool) {mCooldown = cool;}
	float GetLaserCool() {return mCooldown;}
	
private:
	float mLaserCooldown;
	float mCooldown;
	class CircleComponent* mCircle;
	class InputComponent* ic;
};