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
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "defs.h"
#include "Item.h"
#include "Ship.h"

Asteroid::Asteroid(Game *game)
	: Actor(game),
	  mCircle(nullptr)
{
	SetName(Enemy);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(ACTOR_DEFAULT_RADIUS);

	// Initialize to random position/orientation
	Vector2 randPos = Random::GetVector(Vector2::Zero,
										Vector2(STAGE_W, STAGE_H));
	// player랑 겹친상태로 렌더링 불가능
	auto mship = GetGame()->GetShip();
	if (!(Intersect(*mCircle, *(mship->GetCircle()))))
	{
		SetPosition(randPos);
	}
	
	// 게임의 난이도를 저장할 임시변수
	float Diff;
	// game의 난이도 가져옴
	if (((Diff = GetGame()->GetDiff()) < 1))
	{
		Diff = 1.0f; //최소한의 난도sale
	}
	//난이도에 따라 체력, 공격력, 속도가 달라짐
	SetHealth(ENEMY1_HEALTH * Diff * 0.3);
	SetDamage(ENEMY1_DAMAGE * Diff * 0.3);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent *sc = new SpriteComponent(this);

	// Stage에 따라 적의 텍스처를 바꾼다.(현재 버그있음, 동시에 여러개의 텍스처가 존재...)
	switch (GetGame()->GetStage()->GetStageNUM())
	{
	case Stage::EFirst:
		SetScale(0.7f);
		
		sc->SetTexture(game->GetTexture("./Assets/Asteroid.png"));
		break;
	case Stage::ESecond:
		SetScale(0.1f);
		mCircle->SetRadius(ACTOR_DEFAULT_RADIUS*5);
		sc->SetTexture(game->GetTexture("./Assets/ice.png"));
		break;
	case Stage::EThird:
		SetScale(0.1f);
		mCircle->SetRadius(ACTOR_DEFAULT_RADIUS*5);
		sc->SetTexture(game->GetTexture("./Assets/rock.png"));
		break;
	}

	// Create a move component, and set a forward speed
	MoveComponent *mc = new MoveComponent(this);
	float fspeed = Random::GetFloatRange(50.0f, 180.0f);
	mc->SetForwardSpeed(fspeed * Diff * 0.3);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	auto mship = GetGame()->GetShip();
	if (GetHealth() <= 0) //죽을 때
	{
		//아이템생성
		Item* item = new Item(GetGame());
		item->SetPosition(GetPosition());
		item->SetRotation(GetRotation());
		SetState(EDead);
	}
	//플레이어와 접촉 
	if (Intersect(*mCircle, *(mship->GetCircle())))
	{
		// 플레이어의 체력을 damage만큼 감소시킨다.
		mship->SetHealth((mship->GetHealth()) - GetDamage());
		//게임에서 사라짐
		SetState(EDead);
	}
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
