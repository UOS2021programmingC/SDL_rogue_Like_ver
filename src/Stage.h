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
        EFirst =0,
        ESecond,
        EThird
    };

    Stage(class Game *game, int n);

    int GetStageNUM() { return mStageNUM; }
    void SetStage(int stage) { mStageNUM = static_cast<STAGE>(stage);}

    void LoadStage();

private:
    class BGSpriteComponent *mBG1;
    class BGSpriteComponent *mBG2;
    STAGE mStageNUM;

};