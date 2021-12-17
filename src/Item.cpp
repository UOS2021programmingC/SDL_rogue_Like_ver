// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------
#include "Item.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "InputComponent.h"
#include "Ship.h"
#include "Laser.h"
#include "defs.h"

Item::Item(Game* game)
	:Actor(game)
	,mDeathTimer(5.0f)
{
	SetName(NoName);
	//item state Random set
	SetItemState((ITEM)(Random::GetIntRange(0,10)));
	
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	switch(GetItemState())
		{
          case Eatk:
            sc->SetTexture(game->GetTexture("./assets/item_ATK.png"));
            break;
          case Espeed:
            sc->SetTexture(game->GetTexture("./assets/item_SPD.png"));
            break;
          case Ehealth:
            sc->SetTexture(game->GetTexture("./assets/item_HP.png"));
            break;
          case Erapid:
            sc->SetTexture(game->GetTexture("./assets/item_RANGE.png"));
            break;
        }
	
	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(80.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle-> SetRadius(10.0f);

	//STAT
	
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
		Laser *mlaser;

			if (Intersect(*mCircle, *(mship->GetCircle())))
		{
			switch (GetItemState())
			{
			case Eatk:
				mship->SettrueDamage(mship->GetDamage() + 1);
				SetState(EDead);
				break;
			case Ehealth:
				mship->SettrueHealth(mship->GetHealth() + 1);
				SetState(EDead);
				break;
			case Espeed:
				mship->GetInputComponent()->PlusMaxForwardSpeed(30.0f);
				SetState(EDead);
				break;
			case Erapid:
				if (mship->GetLaserCool() < LASER_COOLDOWN)
				{
					mship->SetLaserCool(mship->GetLaserCool() + 0.02f);
				}
				SetState(EDead);
				break;
			}
		}
	}
}
