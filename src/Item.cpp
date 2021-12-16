
#include "Item.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "Ship.h"

#include "defs.h"

Item::Item(Game* game)
	:Actor(game)
	,mDeathTimer(2.0f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("./assets/item_ATK.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);

	//STAT
	SetDamage(PLAYER_DAMAGE);
	
}

void Item::UpdateActor(float deltaTime)
{
	// If we run out of time, Item is dead
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
	    // Do we intersect with ship
        auto mship = GetGame()->GetShip();
		if (Intersect(*mCircle, *(mship->GetCircle())))
		{
			mship->SetDamage(mship->GetDamage()+1);
			SetState(EDead);
		}
	}
}
