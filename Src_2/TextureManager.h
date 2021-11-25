#ifndef TEXTUREMANGER_H
#define TEXTUREMANGER_H

#include "Game.h"
#include "defs.h"

class TextureManager{

    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#endif //TEXTUREMANGER_H