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
