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
	SetPosition(Vector2(CENTER_POSITION_X, CENTER_POSITION_Y));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("./Assets/Portal.png"));

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(ACTOR_DEFAULT_RADIUS);
}

void Portal::UpdateActor(float deltaTime)
{

	auto ship = GetGame()->GetShip();
	//플레이어와 접촉 시
	if (Intersect(*mCircle, *(ship->GetCircle())))
	{	
		//포탈 사라짐
		SetState(EDead);
	}
}