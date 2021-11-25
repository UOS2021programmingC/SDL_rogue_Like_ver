#pragma once

#include "Collision.h"



/*
 *두 사ㄱ각형의 좌표를 이용하여
 *충돌을 감지하는 함수.
 * default는 false이며, 충돌하면 True를 return한다.
 */

 /*
 *(단, 사각형이 수평 or 수직으로 움직여서 만났을때만 작동.)
 *(사각형이 아닌 다른형태로 한다면 될지도? 원이나 그런거)  
 *(완성해보고 디버깅필요하다하면 고치기)
 */

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{   
    if(
        recA.x + recA.w >= recB.x && 
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y && 
        recB.y + recB.h >= recA.y){
        return true;
        }

    return false;
}