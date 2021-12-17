#pragma once
#include "Actor.h"
class Portal : public Actor
{
public:
	Portal(class Game* game);
	~Portal();
	void UpdateActor(float deltaTime) override;
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};
