#ifndef SPR_COMPO_H
#define SPR_COMPO_H

#include "../defs.h"
#include "Components.h"

class SpriteComponent : public Component 
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:

    SpriteComponent() = default; //SpriteComponent(){} 와 같음.
    //Texture Switching 가능
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {   
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = OBJSIZE;
        destRect.w = destRect.h = PLAYER_SIZE;
    }

    void update() override
    {   
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

};

#endif