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
class Laser : public Actor
{
public:
	Laser(class Game* game);

	void UpdateActor(float deltaTime) override;

private:
	class CircleComponent* mCircle;
	float mDeathTimer;

};
