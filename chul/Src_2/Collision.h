#pragma once

#include "defs.h"

class Collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); //check whether two Rects are overlapped or not

};