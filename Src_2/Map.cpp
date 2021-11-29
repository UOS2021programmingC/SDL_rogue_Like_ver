#include "Map.h"



Map::Map()
{
    // dirt = TextureManager::LoadTexture("./assets/dirt.png");
    // grass = TextureManager::LoadTexture("./assets/grass.png");
    // water = TextureManager::LoadTexture("./assets/water.png");

    // //LoadMap(1);
    
    // src.x = src.y = 0;
    // src.w = dest.w = OBJSIZE;
    // src.h = dest.h = OBJSIZE;

    // dest.x = dest.y = 0;
}

Map::~Map() //clean memory
{
    // SDL_DestroyTexture(grass);
    // SDL_DestroyTexture(water);
    // SDL_DestroyTexture(dirt);
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++) 
        {
            mapFile.get(tile);
            Game::AddTile(atoi(&tile), x*OBJSIZE, y*OBJSIZE);
            mapFile.ignore();
        }
    }
    
}



#if 0
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
#endif