#define NOTDEBUG
#if 0  NOTDEBUG
#include "ttf.h"

#include "SpriteComponent.h"
#include "Game.h"
#include "Random.h"
#include "Ship.h"
#include "defs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Ttf::Ttf(Game *game)
    : Actor(game)
{
    renderer = GetGame()->GetRenderer();
    font = TTF_OpenFont("",20);
    
}
void Ttf::render_text(
    SDL_Renderer *renderer,
    int x,
    int y,
    const char *text,
    TTF_Font *font,
    SDL_Rect *rect,
    SDL_Color *color)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;
    /* This is wasteful for textures that stay the same.
     * But makes things less stateful and easier to use.
     * Not going to code an atlas solution here... are we? */
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}
#endif