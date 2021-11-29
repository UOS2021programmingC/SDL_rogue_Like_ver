#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../Game.h"//순환 dependancy 조심 
#include "Components.h"

class Game;

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if(Game::event.type ==SDL_KEYDOWN)//key pressed
        {
            switch(Game::event.key.keysym.scancode)// sym= virtual key code, scancode = physical
            {
                case SDL_SCANCODE_W:
                    transform->velocity.y = -1;
                    sprite->Play("Walk");
                    break;
                case SDL_SCANCODE_A:
                    transform->velocity.x = -1;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDL_SCANCODE_D:
                    transform->velocity.x = 1;
                    sprite->Play("Walk");
                    break;
                case SDL_SCANCODE_S:
                    transform->velocity.y = 1;
                    sprite->Play("Walk");
                    break;
                default:
                break;
            } 
        }
        if(Game::event.type ==SDL_KEYUP)//key released, set velocity = 0;
        {
             switch(Game::event.key.keysym.scancode)// sym= virtual key code, scancode = physical
            {
                case SDL_SCANCODE_W:
                    transform->velocity.y = 0;
                    sprite->Play("Idle");
                    break;
                case SDL_SCANCODE_A:
                    transform->velocity.x = 0;
                    sprite->Play("Idle");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDL_SCANCODE_D:
                    transform->velocity.x = 0;
                    sprite->Play("Idle");
                    break;
                case SDL_SCANCODE_S:
                    transform->velocity.y = 0;
                    sprite->Play("Idle");
                    break;
                default:
                break;
            }  
        }

    }

};


#endif