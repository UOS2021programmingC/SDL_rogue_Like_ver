#include "Portal.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "defs.h"
#include "Item.h"
#include "Ship.h"

Portal::Portal(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	// Initialize to random position/orientation
	Vector2 randPos = Random::GetVector(Vector2::Zero,
		Vector2(1024.0f, 768.0f));
	if (randPos.x != GetGame()->GetShip()->GetPosition().x ||
		randPos.y != GetGame()->GetShip()->GetPosition().y)
		{SetPosition(randPos);}


	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("./Assets/Portal.png"));
    //체력 추가
	SetHealth(PORTAL_HEALTH);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	// Add to mAsteroids in game
	game->AddPortal(this);
}

void Portal::UpdateActor(float deltaTime)
{
	if (GetHealth() <= 0)
	{
		SetState(EDead);
	}

}

Portal::~Portal()
{
	GetGame()->RemovePortal(this);
}
