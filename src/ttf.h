// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------
#if 0 NOTDEBUG

#pragma once
#include "Actor.h"

class Ttf : public Actor
{
public:
    Ttf(class Game *game);

    void UpdateActor(float deltaTime) override;
    void render_text(
        SDL_Renderer *renderer,
        int x,
        int y,
        const char *text,
        TTF_Font *font,
        SDL_Rect *rect,
        SDL_Color *color);
    
    void Render_Health();

    SDL_Renderer *renderer;
    SDL_Window *window;
    int x;
    int y;
    const std::string text;
    // const char *text;
    TTF_Font *font;
    SDL_Rect *rect;
    SDL_Color *color;


private:

};
#endif 