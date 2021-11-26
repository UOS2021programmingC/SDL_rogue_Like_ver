#ifndef COLLISION
#define COLLISION

#include "defs.h"
#include "ECS/ColliderComponent.h"

class ColliderComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); //check whether two Rects are overlapped or not
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB); //check whether two colliders...
};

#endif