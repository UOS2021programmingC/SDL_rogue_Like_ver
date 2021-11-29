#ifndef SPR_COMPO_H
#define SPR_COMPO_H

#include "Components.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component 
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100; //delay between frames.

public:

    int animIndex = 0;

    std::map<const char*, Animation> animations;

    SpriteComponent() = default; //SpriteComponent(){} 와 같음.
    //Texture Switching 가능
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    SpriteComponent(const char* path, bool isAnimated)
    {
        animated = isAnimated;

        Animation idle = Animation(0, 2, ANI_SPEED);
        Animation walk = Animation(1, 4, ANI_SPEED);

        animations.emplace("Idle",idle);
        animations.emplace("Walk", walk);

        Play("Idle");

        setTex(path);
    }

    ~SpriteComponent() //clean memory
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {   
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform-> width;
        srcRect.h = transform-> height;
        
    }

    void update() override
    {   
        if(animated)
        {
            srcRect.x = srcRect.w  * static_cast<int>((SDL_GetTicks()/speed)% frames);
        }
        
        srcRect.y = animIndex * transform -> height;

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

};

#endif