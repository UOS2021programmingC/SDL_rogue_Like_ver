#ifndef DEFS_H
#define DEFS_H



#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>
#include <fstream>


#define PLAYER_SIZE (64)
#define FPS (60)
#define FRAMEDELAY (1000 / FPS)
#define OBJSIZE (32)

#define mapTile_row (20)
#define mapTile_column (25)

#define MAX_COMPONENETS (32)
#define MAX_GROUPS (32)


#define WINDOW_WIDTH (OBJSIZE * mapTile_column)   //800
#define WINDOW_HEIGHT (OBJSIZE * mapTile_row)     //640

#define SPEED_DEFAULT (3)  //entity 이동속도
#define SCALE (1)           //draw scale



#endif