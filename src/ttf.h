// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------
/**
 * @brief SDL_ttf구현을 위한 클래스 구현
 * 
 *      그러나, 실패했다.(디버깅필요)
 */

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