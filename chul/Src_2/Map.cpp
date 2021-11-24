#include "Map.h"

// int lv1_map[20][25] = {{0}};

Map::Map()
{
    dirt = TextureManager::LoadTexture("./assets/dirt.png");
    grass = TextureManager::LoadTexture("./assets/grass.png");
    water = TextureManager::LoadTexture("./assets/water.png");

    //LoadMap(1);
    
    src.x = src.y = 0;
    src.w = dest.w = OBJSIZE;
    src.h = dest.h = OBJSIZE;

    dest.x = dest.y = 0;
}

void Map::LoadMap(int maplv)
{
    FILE *myFile;
        switch(maplv){

            case 1 : 
                myFile = fopen("./map/map1.txt", "r");
                break;
            case 2 : 
                myFile = fopen("./map/map2.txt", "r");
                break;
        }
    
    //read file into array
    for (int i = 0; i < mapTile_row; i++)
    {
        for(int j = 0 ; j<mapTile_column ; j++)
        {
            fscanf(myFile, "%d", &map[i][j]);
            // map[mapTile_row][mapTile_column] = arr[mapTile_row][mapTile_column];
        }
    }
}

void Map::DrawMap()
{
    int type=0;
    for (int i = 0; i < mapTile_row; i++)
    {
        for(int j = 0 ; j<mapTile_column ; j++)
        {
            type = map[i][j];

            dest.x = j*OBJSIZE;
            dest.y = i*OBJSIZE;

            switch(type)
            {
                case 0: 
                TextureManager::Draw(water,src,dest);
                break;
                case 1: 
                TextureManager::Draw(grass,src,dest);
                break;
                case 2: 
                TextureManager::Draw(dirt,src,dest);
                break;

                default:
                break;
            }
        }
    }
}
