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

#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Ship.h"
#include "defs.h"

Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(LASER_LIFE)
{
	SetName(NoName);
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("./Assets/Laser.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(LASER_SPD);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(LASER_RADIUS);

	//STAT
	SetDamage(PLAYER_DAMAGE);
	
}

void Laser::UpdateActor(float deltaTime)
{
	// If we run out of time, laser is dead
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		// Do we intersect with an asteroid?
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				// damage
				auto ship = GetGame()->GetShip();
				ast->SetHealth((ast->GetHealth()) - ship->GetDamage());
				SetState(EDead);
			}
		}
	}
}
