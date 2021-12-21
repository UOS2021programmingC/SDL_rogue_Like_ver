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

#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner)
:Component(owner)
,mRadius(0.0f)
{}

//중심좌표
const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

//반지름 return
float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

//충돌여부 확인
bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// Calculate distance squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
