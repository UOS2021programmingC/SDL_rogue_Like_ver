// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Laser.h"
#include "defs.h"
#include "Item.h"
#include "Portal.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.8f)
	,mCooldown(0.0f)
{
	SetName(Player);
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("./Assets/Ship.png"));

	// Create an input component and set keys/speed
	ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(MAX_SPEED_forward);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	//STAT
	SetHealth(PLAYER_HEALTH);
	SetDamage(PLAYER_DAMAGE);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	if (GetHealth() <= 0)
	{
		SetState(EDead);
	}
	// Do we intersect with an asteroid?

}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// Set laser cooldown
		mLaserCooldown = LASER_COOLDOWN - mCooldown;
	}
	if (GetHealth() <=0)
	{
		SetState(EDead);
	}
}
