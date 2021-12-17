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

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

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
	
	//STAT Getter/setters
	void SetHealth(int health) {mhealth = health;} //난도영향받음
	void SettrueHealth(int health) { mhealth = health;} //난도영향없음
	int GetHealth(){return mhealth;}
	void SetDamage(int damage) { mdamage = damage; }
	void SettrueDamage(int damage) { mdamage = damage;}
	int GetDamage(){return mdamage;}

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
	int mhealth;
	int mdamage;
	float mDiff;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};