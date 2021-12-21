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
#include "Component.h"
#include "Math.h"

/**
 * @brief 충돌 구현을 위한 구성요소 
 * actor의 postion 좌표값의 거리를 구하고,
 * 이와 각자 CircleComponent의 반지름과 비교하여 
 * 충돌여부를 감지한다.
 */
class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);
	
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	
	const Vector2& GetCenter() const;
private:
	float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);
