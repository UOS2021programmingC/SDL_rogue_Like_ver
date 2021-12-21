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
#include "Actor.h"
/**
 * @brief 플레이어를 위한 클래스. 액터의 일종.
 * 플레이어의 키보드 입력 keystate배열에 설정한다.
 * 플레이어의 공격 입력에 대한 동작을 관리한다.
 */
class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	class CircleComponent* GetCircle() { return mCircle; }
	class InputComponent* GetInputComponent() { return ic; }
	
	void SetLaserCool(float cool) {mCooldown = cool;}
	float GetLaserCool() {return mCooldown;}
	
private:
	float mLaserCooldown;
	float mCooldown;
	class CircleComponent* mCircle;
	class InputComponent* ic;
};