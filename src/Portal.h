/**
 * @file Portal.h
 * @author JeongCHul (jeongchul0098@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-22
 */

/**
 * @brief Potal을 위한 클래스 하나의 Actor로서
 * RESETTER tag를 달고 있다.
 * 
 * 플레이어와의 접촉을 트리거로 상호작용한다.
 */
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
