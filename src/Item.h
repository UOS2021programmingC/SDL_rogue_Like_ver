// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------
#pragma once

#include "Actor.h"
class Item : public Actor
{
public:
	enum ITEM
	{
		Eatk,
		Espeed,
		Ehealth,
		Erapid
	};

	Item(class Game* game);

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCircle() { return mCircle; }

	ITEM GetItemState() const { return mItem; }
	void SetItemState(ITEM item) { mItem = item; }

private:
	class CircleComponent* mCircle;
	float mDeathTimer;
	ITEM mItem;
};
