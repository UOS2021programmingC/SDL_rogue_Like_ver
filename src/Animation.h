#pragma once 

struct Animation
{
    int index;
    int frames;
    int speed;
    bool isanimated = true;

    Animation(){};
    Animation(int i, int f, int s)
    {
        index =i;
        frames = f;
        speed = s;
    }

};

