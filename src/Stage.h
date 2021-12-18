// Made by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------

#pragma once

#include "Actor.h"
class Stage : public Actor
{
public:
    enum STAGE
    {
        EFirst,
        ESecond
    };

    Stage(class Game *game, int n);

    int GetStage() { return mStageNUM; }
    void SetStage(int stage) { mStageNUM = stage;}

    void LoadStage();

private:
    class BGSpriteComponent *mBG1;
    class BGSpriteComponent *mBG2;
    int mStageNUM;

};