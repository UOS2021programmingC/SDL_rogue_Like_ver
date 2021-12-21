// ----------------------------------------------------------------
// Updated by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------
#include "BGSpriteComponent.h"
#include "Game.h"
#include "defs.h"
#include "Stage.h"
#include "Math.h"

Stage::Stage(Game *game, STAGE stage)
    : Actor(game)
{
    SetStage(stage);
    SetName(NoName);
    SetPosition(Vector2(CENTER_POSITION_X, CENTER_POSITION_Y));

    // Create the "far back" background
    mBG1 = new BGSpriteComponent(this);
    mBG2 = new BGSpriteComponent(this, 50);
    mBG1->SetScreenSize(Vector2(STAGE_W, STAGE_H));
    mBG2->SetScreenSize(Vector2(STAGE_W, STAGE_H));
    LoadStage();
}

void Stage::LoadStage()
{
    std::vector<SDL_Texture *> bgtexs;
    std::vector<SDL_Texture *> bgtexs2;
    switch (mStageNUM)
    {
    case EFirst:
        bgtexs = {
            GetGame()->GetTexture("Assets/Farback01.png"),
            GetGame()->GetTexture("Assets/Farback02.png")};
        bgtexs2 = {
            GetGame()->GetTexture("Assets/Stars.png"),
            GetGame()->GetTexture("Assets/Stars.png")};
        break;
    case ESecond:
        bgtexs = {
            GetGame()->GetTexture("Assets/cave.png"),
            GetGame()->GetTexture("Assets/cave.png")};
        break;
    case EThird:
        bgtexs = {
            GetGame()->GetTexture("Assets/ice_back.png"),
            GetGame()->GetTexture("Assets/ice_back.png")};
        break;
    }
    mBG1->SetBGTextures(bgtexs);
    mBG1->SetScrollSpeed(STAGE_SPD);
    mBG2->SetBGTextures(bgtexs2);
    mBG2->SetScrollSpeed(STAGE_SPD);
}