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
	,mDeathTimer(ITEM_LIFE) //5초후 자동 사라짐
{
	SetName(NoName);
	//item state Random set
	SetItemState((ITEM)(Random::GetIntRange(0,8)));
	
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
	mc->SetForwardSpeed(ITEM_SPD); //아이템이동속도

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(ITEM_RADIUS);

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
			//아이템에 따라 기능부야.
			switch (GetItemState())
			{
				//플레이어 공격력 증가.
			case Eatk:
				mship->SetDamage(mship->GetDamage() + ITEM_ATK);
				SetState(EDead);
				break;
				//플레이어 체력증가.
			case Ehealth:
				mship->SetHealth(mship->GetHealth() + ITEM_HP);
				SetState(EDead);
				break;
				//플레이어 속도 증가.
			case Espeed:
				mship->GetInputComponent()->PlusMaxForwardSpeed(ITEM_SPD);
				SetState(EDead);
				break;
				//플레이어 발사속도 증가.
			case Erapid:
				if (mship->GetLaserCool() < LASER_COOLDOWN)
				{
					mship->SetLaserCool(mship->GetLaserCool() + ITEM_RPD);
				}
				SetState(EDead);
				break;
			}
		}
	}
}
