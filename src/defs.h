/**
 * @file defs.h
 * @author JeongCHul (jeongchul0098@gmail.com)
 * @brief 매크로상수를 모아놓은 헤더파일
 * @version 0.1
 * @date 2021-12-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#define ACTOR_DEFAULT_RADIUS 40.0f

#define CENTER_POSITION_X  512.0f
#define CENTER_POSITION_Y 384.0f

//DEFAULT STAT
#define PLAYER_HEALTH 5
#define PLAYER_DAMAGE 1

#define ENEMY1_HEALTH 1
#define ENEMY1_DAMAGE 1

//LASER
#define LASER_COOLDOWN 0.2f
#define LASER_LIFE  0.6f
#define LASER_SPD 1000.0f
#define LASER_RADIUS 11.0f


//PLAYER
#define MAX_SPEED_forward 300.0f

//ITEM DEFAULT STAT
#define ITEM_HP 1
#define ITEM_ATK 1
#define ITEM_SPD 80.0f
#define ITEM_RPD 0.05f 
#define ITEM_RADIUS 10.0f
#define ITEM_LIFE 5.0f

//stage
#define STAGE_W 1024.0f
#define STAGE_H 768.0f
#define STAGE_SPD (-50.0f)
