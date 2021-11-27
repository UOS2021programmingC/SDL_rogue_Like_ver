#ifndef TILE
#define TILE

#include "Components.h"


// #define ARRAY  //if def ARRAY, mapTile sys runs with txt;


class TileComponent : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID; //tile tag
    const char* path; //tile texture path

#ifdef ARRAY
    FILE *tiletxt;
    int map[mapTile_row][mapTile_column];
#endif

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x; 
        tileRect.y = y; 
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID) {
          case 0:
            path = "assets/water.png";  // 0=water
            break;
          case 1:
            path = "assets/grass.png";  // 1=grass
            break;
          case 2:
            path = "assets/dirt.png";  // 2=dirt
            break;
          default:
            break;
        }
    }

    void init() override
    {
        entity -> addComponent<TransformComponent>((float)tileRect.x,(float)tileRect.y,tileRect.w,tileRect.h, SCALE);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }  

#ifdef ARRAY     
        switch (tileID) {
          case 1:
            tiletxt = fopen("./map/map1.txt", "r");
            break;
          case 2:
            tiletxt = fopen("./map/map2.txt", "r");
            break;
        }

        // read file into array
        for (int i = 0; i < mapTile_row; i++) {
          for (int j = 0; j < mapTile_column; j++) {
            fscanf(tiletxt, "%d", &map[i][j]);
          }
        }
#endif
};
#endif

