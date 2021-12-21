// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
// Updated by Chul 9&J teams
// in C_programing project in Mechanical Informaion Engineering UOS, 2021.
// ----------------------------------------------------------------


#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"
/**
 * @brief 움직이는 배경을 위한 SpriteComponent인  BGSpriteComponent.
 * 텍스쳐를 벡터형식으로 여러개 가지고있는다.
 * 그것을 바탕으로 순차적으로 이미지를 붙인다.(파노라마 구현)
 * 그후 속도를 주어 움직이게 만든다.
 */
class BGSpriteComponent : public SpriteComponent
{
public:
	// Set draw order to default to lower (so it's in the background)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// Update/draw overridden from parent
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// Set the textures used for the background
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// Get/set screen size and scroll speed
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};
