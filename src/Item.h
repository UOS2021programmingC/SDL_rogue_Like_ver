/**
 * @file Item.cpp
 * @author JeongCHul (jeongchul0098@gmail.com)
 * @brief Item객체를 위한 Class, Actor중 하나로 존재.움직임과 충돌을
 * 가ㅣㅁ지하는 구성요소를 가진다.
 * @version 0.1
 * @date 2021-12-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "Actor.h"
class Item : public Actor
{
public:
	//아이템의 종류를 나누는 enum
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
