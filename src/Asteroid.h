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
#include "Stage.h"

/**
 * @brief
 * 적의 태그네임을 가진 Actor
 * 플레이와의 접촉시 체력을 감소시키고 사라진다.
 * 사망시 확률적으로  무작위 아이템 Actor를 생성하고 사라진다.
 */
class Asteroid : public Actor
{
public:

	Asteroid(class Game *game);
	~Asteroid();
	void UpdateActor(float deltaTime) override;
	class CircleComponent* GetCircle() { return mCircle; }

private:
	class CircleComponent* mCircle;
	class Stage* mStage;

};
