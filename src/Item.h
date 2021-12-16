#pragma once

#include "Actor.h"
class Item : public Actor
{
public:
	Item(class Game* game);
	
	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
	float mDeathTimer;
};
