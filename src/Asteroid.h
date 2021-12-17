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
class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();
	void UpdateActor(float deltaTime) override;
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};
