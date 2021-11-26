#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../Game.h"//순환 dependancy 조심 
#include "Components.h"

class Game;

class KeyboardController : public Component
{
public:
    TransformComponent *transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        if(Game::event.type ==SDL_KEYDOWN)//key pressed
        {
            switch(Game::event.key.keysym.scancode)// sym= virtual key code, scancode = physical
            {
                case SDL_SCANCODE_W:
                    transform->velocity.y = -1;
                    break;
                case SDL_SCANCODE_A:
                    transform->velocity.x = -1;
                    break;
                case SDL_SCANCODE_D:
                    transform->velocity.x = 1;
                    break;
                case SDL_SCANCODE_S:
                    transform->velocity.y = 1;
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
                    break;
                case SDL_SCANCODE_A:
                    transform->velocity.x = 0;
                    break;
                case SDL_SCANCODE_D:
                    transform->velocity.x = 0;
                    break;
                case SDL_SCANCODE_S:
                    transform->velocity.y = 0;
                    break;
                default:
                break;
            }  
        }

    }

};


#endif