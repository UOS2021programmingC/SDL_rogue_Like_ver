// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------
#pragma once
#include "Actor.h"
class Portal : public Actor
{
public:
	Portal(class Game* game);
	
	void UpdateActor(float deltaTime) override;
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};
