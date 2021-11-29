#ifndef ANI_H
#define ANI_H

#include "../defs.h"

struct Animation
{
    int index;
    int frames;
    int speed;

    Animation(){};
    Animation(int i, int f, int s)
    {
        index =i;
        frames = f;
        speed = s;
    }
};


#endif