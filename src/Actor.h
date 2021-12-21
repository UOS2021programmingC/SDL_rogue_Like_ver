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
#include <vector>
#include "Math.h"
#include <cstdint>
/**
 * @brief Actor
 * 게임에서 하나의 객체를 다루기 위한 클래스이다.
 * 객체의  위치정보, 렌더링사이즈, 체력 등이 모두 포함되어 있다.
 * 추가적인 구성요소를 벡터형식으로 저장한다.
 */
class Actor
{
public:
	/** Tag State name ,
	 * @param EActive : 살아있는 상태, 게임에 존재한다.
	 * @param EPaused : 정지 상태, 게임에서 사라지지는 않는다.
	 * @param EDdead : 죽은 상태, 게임에서 사라지게 된다.
	 */
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	/** Tag Actor name , 
	 * @param player : 플레이어. 적과 리셋터 등과 상호작용한다.
	 * @param Enemy : 적의 특성, 플레이어와 닿으면 사라지며 플레이어에게 데미지를 준다.
	 * @param NoName : 아무런 특성을 가지지 않는다
	 * @param RESETTER : 닿으면 스테이지와 적의 소환을 변경한다.
	*/
	enum Name
	{
		Player,
		Enemy,
		NoName,
		RESETTER
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	// STAT Getter/setters
	void SetHealth(float health) {mhealth = health;} 
	void SetDamage(float damage) { mdamage = damage; }
	
	float GetDamage(){return mdamage;}
	float GetHealth() { return mhealth; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	Name GetName() const { return mName; }
	void SetName(Name name) {mName = name; }

	class Game* GetGame() { return mGame; }

	
	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State mState;
	Name mName;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	//CUSTOM stat
	float mhealth;
	float mdamage;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};