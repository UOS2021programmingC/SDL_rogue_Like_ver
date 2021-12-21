// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------

#include "Portal.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "defs.h"
#include "Item.h"
#include "Ship.h"
#include "Stage.h"

Portal::Portal(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{	
	SetName(RESETTER);
	SetPosition(Vector2(512.0f, 384.0f));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("./Assets/Portal.png"));

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);
}

void Portal::UpdateActor(float deltaTime)
{

	auto ship = GetGame()->GetShip();
	// auto stage = GetGame()->GetStage();
	if (Intersect(*mCircle, *(ship->GetCircle())))
	{	
		SetState(EDead);
	}
}
// Portal::~Portal()
// {
// 	GetGame()->RemovePortal(this);
// }
