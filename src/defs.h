#pragma once

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

#define ANI_SPEED  (200)