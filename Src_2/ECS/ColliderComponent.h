#pragma Once

#include "../defs.h"
#include "Components.h"


class ColliderComponent : public Component 
{
public:
    SDL_Rect collider;
    std::string tag; //player tag, enemy tag 처럼 충돌하는 물체의 tag

    TransformComponent* transform;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }


};