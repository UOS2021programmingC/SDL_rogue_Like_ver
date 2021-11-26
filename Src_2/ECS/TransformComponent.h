#ifndef POS_COMPO_H
#define POS_COMPO_H

#include "Components.h"
//../ 현재위치의 상단폴더
#include "../Vector2D.h"

struct TransformComponent : public Component
{

public:
      
    Vector2D position;
    Vector2D velocity;

    int height = OBJSIZE;
    int width = OBJSIZE;
    int scale = 1;
    int speed = SPEED_DEFAULT;

//override: 이 가상함수가 상속받아서 오버라이딩한 함수다...

    TransformComponent() 
    {
        position.Zero();
    }

    TransformComponent(int sc) 
    {
        position.Zero();
        scale = sc;
    }

    TransformComponent(float x, float y)
    {
        // position.x =x;
        // position.y =y;
        position.Zero();
    }

     TransformComponent(float x, float y, int w, int h, int sc)
    {
        position.x =x;
        position.y =y;
        height = h;
        width = width;
        scale = sc;
    }

    void init() override 
    {
        // position.x = 0.0f;
        // position.y = 0.0f;
        velocity.Zero();
    }

    void update() override 
    {
        // position.x++;
        // position.y++;
        position.x += velocity.x*speed;
        position.y += velocity.y*speed;
    }

};

#endif