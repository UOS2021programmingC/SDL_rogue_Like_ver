#ifndef MAP_H 
#define MAP_H 

#include "defs.h"
#include "TextureManager.h"
class Map
{
public:

    Map();
    ~Map();

    void LoadMap(int maplv);
    void DrawMap();

private:

    SDL_Rect src, dest;  //src=source , dest = destination

    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    int map[mapTile_row][mapTile_column];
    

};

#endif