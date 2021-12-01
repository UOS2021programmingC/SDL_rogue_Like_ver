#ifndef MAP_H 
#define MAP_H 

#include "Game.h"
#include "defs.h"
// #include "TextureManager.h"

class Map
{
public:

    Map();
    ~Map();

    static void LoadMap(std::string path, int sizeX, int sizeY);
    
    // void DrawMap();

private:

#if 0
    SDL_Rect src, dest;  //src=source , dest = destination

    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    int map[mapTile_row][mapTile_column];
#endif  


};

#endif